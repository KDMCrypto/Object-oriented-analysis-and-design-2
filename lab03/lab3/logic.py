import cv2
from abc import ABC, abstractmethod
import numpy as np
from PIL import Image
from pathlib import Path
import ollama
import time
import psutil, os
import gc

# абстрактный класс обработчика
class ImageHandler(ABC):
    def __init__(self):
        self.next = None

    def set_next(self, handler):
        self.next = handler
        return handler

    def handle_request(self, context):
        context = self.process(context)

        if self.next:
            return self.next.handle_request(context)

        return context

    @abstractmethod
    def process(self, context):
        pass

# класс для данных
class ImageContext:
    def __init__(self, image_path, output_path):
        self.image_path = image_path
        self.markdown = ""
        self.output_path = output_path

        self.image: np.Optional[np.ndarray] = None       # Сюда ляжет 'input_img'
        self.layout_boxes: list[dict[str, any]] = []     # Сюда ляжет список 'boxes'
        self.recognized_texts: list[dict[str, any]] = [] # Результаты OCR
        self.saved_images = []

class OpenImageHandler(ImageHandler):
    def process(self, context: 'ImageContext') -> 'ImageContext':

        print(f"[LOG] Проверка файла: {context.image_path}")

        # Проверка существования
        path = Path(context.image_path)
        if not path.exists():
            raise FileNotFoundError(f"Файл не найден по пути: {path}")

        # Проверка расширения
        valid_extensions = {'.jpg', '.jpeg', '.png', '.bmp', '.webp'}
        if path.suffix.lower() not in valid_extensions:
            raise ValueError(f"Неподдерживаемый формат файла: {path.suffix}")

        # Попытка открытия
        #image = cv2.imread(str(path))

        try:
            # Читаем файл как массив байтов (это обходит проблему путей Windows)
            file_bytes = np.fromfile(str(path), dtype=np.uint8)
            # Декодируем массив в изображение OpenCV
            image = cv2.imdecode(file_bytes, cv2.IMREAD_COLOR)
        except Exception as e:
            raise ValueError(f"Ошибка при чтении файла через буфер: {e}")
        
        # Если OpenCV вернул None, значит файл битый или это не картинка
        if image is None or image.size == 0:
            raise ValueError(f"Не удалось декодировать изображение. Возможно, файл поврежден: {path}")

        # Если всё успешно — сохраняем в контекст
        context.image = image
        
        h, w = image.shape[:2]
        print(f"[LOG] Успешно загружено: {w}x{h} пикселей")

        return context


# обработчик для детекции блоков
class LayoutHandler(ImageHandler):
    def __init__(self, layout_model):
        super().__init__()
        self.model = layout_model

    def process(self, context: 'ImageContext') -> 'ImageContext':
        output = self.model.predict(input=context.image, batch_size=1, layout_nms=True)

        boxes = output[0]['boxes']
        
        # обработка пустого результата
        if not boxes or len(boxes) == 0:
            raise ValueError("На изображении не найдено ни одного элемента (текста, картинок или таблиц). Распознавание прервано.")

        context.layout_boxes = boxes

        return context
    
# обработчик для считывания текста
class OCRHandler(ImageHandler):
    def __init__(self, model_name):
        super().__init__()

        self.model_name = model_name

    def qwen_ocr(self, cropped_img):

        h, w = cropped_img.shape[:2]

        if h < 40 or w < 40:
            top = bottom = (64 - h) // 2 if h < 64 else 0
            left = right = (64 - w) // 2 if w < 64 else 0
            # Добавляем белую рамку
            cropped_img = cv2.copyMakeBorder(
                cropped_img, top, bottom, left, right, 
                cv2.BORDER_CONSTANT, value=[255, 255, 255]
            )

        # Конвертируем OpenCV изображение в байты PNG
        success, buffer = cv2.imencode(".png", cropped_img)
        if not success:
            return ""
            
        image_bytes = buffer.tobytes()

        prompt = (
            "You are an expert OCR assistant. "
            "Extract all text from this image exactly as it is written. "
            "Maintain the original formatting: preserve headers, paragraphs, and lists. "
            "If you see a table, represent it as a Markdown table. "
            "Output in Russian language. Do not add any comments, just the extracted text."
        )
        # Запрос к Ollama
        response = ollama.chat(
            model=self.model_name,
            messages=[
                {
                    'role': 'user',
                    'content': prompt,
                    'images': [image_bytes]
                }
            ],
            options={
                    'temperature': 0,      # Убираем креативность для точности OCR
                },
            think=False
        )

        return response['message']['content']

    def process(self, context: 'ImageContext') -> 'ImageContext':

        text_labels = {'text', 'paragraph_title', 'figure_title', 'chart_title', 'table_title', 'number', 'doc_title'} #'formula'

        for box in context.layout_boxes:
            label = box['label']
            if label in text_labels:
                x_min, y_min, x_max, y_max = map(int, box['coordinate'])

                cropped_img = context.image[y_min:y_max, x_min:x_max]

                if cropped_img.size == 0:
                    continue

                recognized_text = self.qwen_ocr(cropped_img)

                if len(recognized_text.strip()) < 2:
                    continue

                context.recognized_texts.append({
                    'label': label,
                    'text': recognized_text,
                    'coordinate': box['coordinate']
                })

        return context

# обработчик который вырезает и сохраняет изображения 
class ImageSaveHandler(ImageHandler):
    def process(self, context: 'ImageContext') -> 'ImageContext':

        base_output = Path(context.output_path).resolve()
        output_dir = base_output / "images"
        output_dir.mkdir(parents=True, exist_ok=True)

        text_labels = {'image', 'table', 'chart'}

        for i, box in enumerate(context.layout_boxes):
            label = box['label']
            if label in text_labels:
                x_min, y_min, x_max, y_max = map(int, box['coordinate'])

                cropped_img = context.image[y_min:y_max, x_min:x_max]

                if cropped_img.size == 0:
                    continue

                crop_name = f"{label}_{i}.png"
                save_path = output_dir / crop_name

                success, buffer = cv2.imencode(".png", cropped_img)
                with open(save_path, "wb") as f:
                            f.write(buffer)

                # cv2.imwrite(str(save_path), cropped_img)

                relative_path = f"images/{crop_name}"

                context.saved_images.append({
                    'label': label,
                    'path': relative_path,
                    'index': i,
                    'x_min': x_min,
                    'y_min': y_min,
                })

        return context

# обработчик который создает финальный markdown
class MarkdownHandler(ImageHandler):
    def process(self, context: 'ImageContext') -> 'ImageContext':
        img_width = context.image.shape[1]
        all_elements = []
        mid_x = img_width / 2

        # Собираем тексты
        for item in context.recognized_texts:
            all_elements.append({
                'type': 'text',
                'label': item['label'],
                'content': item['text'],
                'y': item['coordinate'][1], # y_min
                'x': item['coordinate'][0]  # x_min
            })

        # Собираем картинки
        for img in context.saved_images:
            all_elements.append({
                'type': 'image',
                'label': img['label'],
                'content': img['path'],
                'y': img['y_min'], 
                'x': img['x_min']
            })

        # сортируем
        all_elements.sort(key=lambda el: (0 if el['x'] < mid_x else 1, el['y']))
        #all_elements.sort(key=lambda el: (el['y'], el['x']))

        md_lines = []
        for el in all_elements:
            if el['type'] == 'text':
                # Стилизуем в зависимости от метки
                if el['label'] == 'doc_title':
                    md_lines.append(f"## {el['content']}\n")
                elif el['label'] == 'paragraph_title':
                    md_lines.append(f"### {el['content']}\n")
                else:
                    md_lines.append(f"{el['content']}\n")
            
            elif el['type'] == 'image':
                # Вставляем ссылку на сохраненный файл
                label_rus = "Изображение" if el['label'] == 'image' else "Таблица"
                md_lines.append(f"![{label_rus}]({el['content']})\n")

        context.final_markdown = "\n".join(md_lines)

        # сохраняем
        report_path = Path(context.output_path) / "output.md"
        with open(report_path, "w", encoding="utf-8") as f:
            f.write("\n".join(md_lines))

        return context