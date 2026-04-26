package lab4_no_pattern;

import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.util.List;
import java.util.stream.Collectors;

public class StatsPanel extends JPanel {
    private IDatabaseService db;
    private JEditorPane textPane = new JEditorPane();

    public StatsPanel(IDatabaseService db) {
        this.db = db;
        setLayout(new BorderLayout());
        textPane.setContentType("text/html");
        textPane.setEditable(false);
        textPane.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        add(new JScrollPane(textPane), BorderLayout.CENTER);
    }

    public void updateData() {
        List<Experiment> list = db.getAllExperiments();
        if (list.isEmpty()) {
            textPane.setText("<html><body><h2>Нет данных для анализа</h2></body></html>");
            return;
        }

        Experiment bestF1 = list.stream().max(Comparator.comparingDouble(Experiment::getF1)).get();
        Experiment fastest = list.stream().min(Comparator.comparingInt(Experiment::getTrainingTime)).get();
        Experiment mostEfficient = list.stream()
                .max(Comparator.comparingDouble(e -> e.getF1() / Math.max(e.getTrainingTime(), 1)))
                .get();

        double[] f1Vals = list.stream().mapToDouble(Experiment::getF1).toArray();
        double[] timeVals = list.stream().mapToDouble(Experiment::getTrainingTime).toArray();
        
        double meanF1 = Arrays.stream(f1Vals).average().orElse(0);
        double stdF1 = Math.sqrt(Arrays.stream(f1Vals).map(v -> Math.pow(v - meanF1, 2)).average().orElse(0));
        double meanTime = Arrays.stream(timeVals).average().orElse(0);
        double stdTime = Math.sqrt(Arrays.stream(timeVals).map(v -> Math.pow(v - meanTime, 2)).average().orElse(0));
        
        int aboveThreshold = (int) Arrays.stream(f1Vals).filter(v -> v > 0.9).count();

        List<Experiment> topF1 = list.stream().sorted(Comparator.comparingDouble(Experiment::getF1).reversed()).limit(3).collect(Collectors.toList());
        List<Experiment> topAcc = list.stream().sorted(Comparator.comparingDouble(Experiment::getAccuracy).reversed()).limit(3).collect(Collectors.toList());
        List<Experiment> topFast = list.stream().sorted(Comparator.comparingInt(Experiment::getTrainingTime)).limit(3).collect(Collectors.toList());

        StringBuilder html = new StringBuilder();
        html.append("<html><body style='font-family: Arial, sans-serif; padding:15px; color: #333;'>");
        html.append("<h2 style='color: #2c3e50; border-bottom: 2px solid #3498db; padding-bottom: 8px;'>📊 Сравнительный анализ моделей</h2>");

        html.append("<table width='100%' cellpadding='8' cellspacing='5' style='margin-bottom: 15px;'><tr>");
        html.append(cardCell(" Лучший F1", bestF1.getModelName(), String.format("%.3f", bestF1.getF1()), "#2980b9"));
        html.append(cardCell(" Самый быстрый", fastest.getModelName(), fastest.getTrainingTime() + " сек", "#c0392b"));
        html.append(cardCell(" Баланс (F1/Время)", mostEfficient.getModelName(), String.format("%.4f", mostEfficient.getF1() / Math.max(mostEfficient.getTrainingTime(), 1)), "#27ae60"));
        html.append("</tr></table>");

        html.append("<div style='background: #f8f9fa; padding: 12px; border: 1px solid #dee2e6; border-radius: 6px; margin-bottom: 15px;'>");
        html.append("<b> Статистика по выборке:</b><br>");
        html.append("• Средний F1: ").append(String.format("<b>%.3f ± %.3f</b>", meanF1, stdF1)).append(" | ");
        html.append(String.format("Моделей с F1 > 0.9: <b>%d/%d</b><br>", aboveThreshold, list.size()));
        html.append("• Среднее время обучения: ").append(String.format("<b>%.1f ± %.1f сек</b>", meanTime, stdTime));
        html.append("</div>");

        html.append("<table width='100%' cellpadding='8' cellspacing='5' style='margin-bottom: 15px;'><tr>");
        html.append(listCell(" Топ-3 по F1", topF1, e -> String.format("%.3f", e.getF1())));
        html.append(listCell(" Топ-3 по Точности", topAcc, e -> String.format("%.3f", e.getAccuracy())));
        html.append(listCell(" Топ-3 по Скорости", topFast, e -> e.getTrainingTime() + " с"));
        html.append("</tr></table>");

        html.append("<h3>📋 Полное сравнение</h3>");
        html.append("<table width='100%' border='1' cellspacing='0' cellpadding='6' style='border-collapse: collapse; border-color: #ddd;'>");
        html.append("<tr style='background-color: #34495e; color: white; font-weight: bold;'>");
        html.append("<th>Модель</th><th>F1</th><th>Prec</th><th>Rec</th><th>Acc</th><th>Время (с)</th><th>Эффективность</th></tr>");

        for (int i = 0; i < list.size(); i++) {
            Experiment e = list.get(i);
            double efficiency = e.getF1() / Math.max(e.getTrainingTime(), 1);
            String bgColor = (i % 2 == 0) ? "#f8f9fa" : "#ffffff";
            String effColor = efficiency > 0.01 ? "#27ae60" : "#7f8c8d";
            
            html.append(String.format("<tr style='background-color: %s;'>", bgColor));
            html.append(String.format("<td><b>%s</b></td>", e.getModelName()));
            html.append(String.format("<td>%.3f</td>", e.getF1()));
            html.append(String.format("<td>%.3f</td>", e.getPrecision()));
            html.append(String.format("<td>%.3f</td>", e.getRecall()));
            html.append(String.format("<td>%.3f</td>", e.getAccuracy()));
            html.append(String.format("<td>%d</td>", e.getTrainingTime()));
            html.append(String.format("<td style='color: %s; font-weight: bold;'>%.4f</td>", effColor, efficiency));
            html.append("</tr>");
        }
        html.append("</table>");

        html.append("<div style='margin-top: 15px; padding: 12px; background: #e8f6f3; border-left: 4px solid #27ae60;'>");
        html.append("<b> Рекомендация системы:</b><br>");
        if (bestF1 == mostEfficient) {
            html.append("Модель <b>").append(bestF1.getModelName()).append("</b> является абсолютным лидером по качеству и эффективности. Рекомендуется к использованию.");
        } else {
            html.append("Для максимальной точности выбирайте <b>").append(bestF1.getModelName()).append("</b>.<br>");
            html.append("Если критично время обучения, используйте <b>").append(fastest.getModelName()).append("</b>.<br>");
            html.append("Оптимальный компромисс обеспечивает <b>").append(mostEfficient.getModelName()).append("</b>.");
        }
        html.append("</div>");

        html.append("</body></html>");
        textPane.setText(html.toString());
    }

    private String cardCell(String title, String model, String value, String color) {
        return String.format(
            "<td style='border: 1px solid #ddd; background: white; vertical-align: top; width: 33%%;'>"+
            "<div style='color: %s; font-size: 18px;'>%s</div>"+
            "<div style='font-size: 14px; margin: 5px 0;'>%s</div>"+
            "<div style='font-size: 20px; font-weight: bold;'>%s</div></td>", 
            color, title, model, value);
    }

    private String listCell(String title, List<Experiment> top, java.util.function.Function<Experiment, String> valGetter) {
        StringBuilder sb = new StringBuilder();
        sb.append("<td style='border: 1px solid #ddd; background: white; vertical-align: top; width: 33%;'>");
        sb.append("<div style='font-weight: bold; margin-bottom: 5px;'>").append(title).append("</div>");
        for (int i = 0; i < top.size(); i++) {
            Experiment e = top.get(i);
            sb.append(String.format("<div style='font-size: 13px;'>%d. %s (%s)</div>", i+1, e.getModelName(), valGetter.apply(e)));
        }
        sb.append("</td>");
        return sb.toString();
    }
}