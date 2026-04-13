import sys
import  transformers 
from pathlib import Path

from PyQt6.QtWidgets import (
    QApplication, QMainWindow, QPushButton, QVBoxLayout, 
    QHBoxLayout, QWidget, QLineEdit, QTextEdit, QLabel, 
    QFileDialog, QTabWidget, QTextBrowser, QScrollArea
)

from PyQt6.QtGui import QPixmap
from PyQt6.QtCore import Qt, QTimer

from paddleocr import LayoutDetection
from logic import *

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("AI Document Parser")
        self.setGeometry(100, 100, 1000, 800)

        self.layout_model = None
        self.chain = None 
        self.models_loaded = False

        self.init_ui()
        
        # Автоматическая загрузка моделей через 100 мс после отрисовки окна
        QTimer.singleShot(100, self.load_models)

    def init_ui(self):
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        main_layout = QVBoxLayout(central_widget)

        # --- Секция путей ---
        path_layout = QHBoxLayout()
        self.path_input = QLineEdit()
        self.path_input.setPlaceholderText("Путь к изображению...")
        btn_browse = QPushButton("Обзор")
        btn_browse.clicked.connect(self.browse_file)
        
        path_layout.addWidget(QLabel("Файл:"))
        path_layout.addWidget(self.path_input)
        path_layout.addWidget(btn_browse)
        main_layout.addLayout(path_layout)

        out_layout = QHBoxLayout()
        self.output_input = QLineEdit()
        self.output_input.setText(str(Path.cwd() / "output"))
        out_layout.addWidget(QLabel("Папка вывода:"))
        out_layout.addWidget(self.output_input)
        main_layout.addLayout(out_layout)

        # --- ВКЛАДКИ (Tabs) ---
        self.tabs = QTabWidget()
        
        # Вкладка 1: Исходное изображение
        self.image_label = QLabel("Выберите файл для отображения")
        self.image_label.setAlignment(Qt.AlignmentFlag.AlignCenter)
        
        # Заворачиваем картинку в ScrollArea на случай большого разрешения
        scroll_area = QScrollArea()
        scroll_area.setWidgetResizable(True)
        scroll_area.setWidget(self.image_label)
        self.tabs.addTab(scroll_area, "🖼️ Исходник")

        # Вкладка 2: Результат (Форматированный Markdown)
        self.result_display = QTextBrowser()
        self.result_display.setOpenExternalLinks(True) # Позволяет кликать по ссылкам/изображениям
        self.result_display.setStyleSheet("background-color: #ffffff; color: #000000; font-size: 15px; font-family: Arial;")
        self.tabs.addTab(self.result_display, "📄 Результат")

        # Вкладка 3: Логи
        self.log_output = QTextEdit()
        self.log_output.setReadOnly(True)
        self.log_output.setStyleSheet("background-color: #1e1e1e; color: #d4d4d4; font-family: Consolas; font-size: 11px;")
        self.tabs.addTab(self.log_output, "⚙️ Логи системы")

        main_layout.addWidget(self.tabs)

        # --- Кнопки управления ---
        self.btn_run = QPushButton("Запустить распознавание")
        self.btn_run.setEnabled(False) # Ждет загрузки моделей
        self.btn_run.clicked.connect(self.start_processing)
        self.btn_run.setStyleSheet("background-color: #2b5b2b; color: white; font-weight: bold; height: 40px;")
        
        main_layout.addWidget(self.btn_run)

    def log(self, message):
        self.log_output.append(f"> {message}")
        self.log_output.verticalScrollBar().setValue(self.log_output.verticalScrollBar().maximum())

    def browse_file(self):
        file_path, _ = QFileDialog.getOpenFileName(self, "Выберите изображение", "", "Images (*.png *.jpg *.jpeg *.bmp)")
        if file_path:
            self.path_input.setText(file_path)     
            # Загружаем и отображаем исходное изображение
            pixmap = QPixmap(file_path)
            # Масштабируем так, чтобы влезло в экран, но не теряло пропорции
            scaled_pixmap = pixmap.scaled(
                self.image_label.width() - 20, 
                self.image_label.height() - 20, 
                Qt.AspectRatioMode.KeepAspectRatio, 
                Qt.TransformationMode.SmoothTransformation
            )
            self.image_label.setPixmap(scaled_pixmap)
            self.tabs.setCurrentIndex(0) # Переключаем на вкладку с картинкой

    def load_models(self):
        if self.models_loaded: return
        try:
            self.log("Инициализация моделей (PP-DocLayout-L и Ollama)...")
            QApplication.processEvents() 
            
            from paddleocr import LayoutDetection
            # Загружаем нейросеть детекции
            self.layout_model = LayoutDetection(model_name="PP-DocLayoutV3") #PP-DocLayoutV3 | PP-DocLayout-L
            
            # Инициализируем единый обработчик
            self.handler = ImageHandler(self.layout_model, model_name='qwen3.5:2b') 

            self.models_loaded = True
            self.btn_run.setEnabled(True)
            self.log("✅ Система готова. Монолитный обработчик инициализирован.")
            self.btn_run.setText("Запустить распознавание")
        except Exception as e:
            self.log(f"❌ Ошибка инициализации: {e}")
            self.btn_run.setText("Ошибка загрузки моделей")

    def start_processing(self):
        img_path = self.path_input.text()
        out_path = self.output_input.text()

        if not img_path:
            self.log("Ошибка: Выберите входной файл!")
            return

        try:
            self.log(f"--- ЗАПУСК ОБРАБОТКИ (БЕЗ ПАТТЕРНА) ---")
            self.btn_run.setEnabled(False)
            self.result_display.clear()
            self.tabs.setCurrentIndex(2) 
            QApplication.processEvents()

            # Создаем контекст данных
            context = ImageContext(img_path, out_path)

            self.log("Шаг 1: Загрузка изображения...")
            context = self.handler.OpenImage(context)
            
            self.log("Шаг 2: Анализ структуры (Layout)...")
            context = self.handler.LayoutHandler(context)
            
            self.log("Шаг 3: Распознавание текста (OCR)... Это может занять время.")
            QApplication.processEvents()
            context = self.handler.OCRHandler(context)
            
            self.log("Шаг 4: Сохранение изображений...")
            context = self.handler.ImageSave(context)
            
            self.log("Шаг 5: Генерация финального документа...")
            context = self.handler.MarkdownHandler(context)

            # Отображение результата
            if hasattr(context, 'final_markdown'):
                resource_path = Path(context.output_path).absolute().as_posix()
                self.result_display.setSearchPaths([resource_path])
                self.result_display.setMarkdown(context.final_markdown)
                
                self.tabs.setCurrentIndex(1) 
                self.log("✅ Обработка завершена успешно.")
            
        except Exception as e:
            self.log(f"❌ ОШИБКА НА ЭТАПЕ ОБРАБОТКИ: {str(e)}")
            self.tabs.setCurrentIndex(2)
        finally:
            self.btn_run.setEnabled(True)

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec())