package lab4_no_pattern;

import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.io.*;

public class CsvPanel extends JPanel {
    private IDatabaseService db;

    public CsvPanel(IDatabaseService db) {
        this.db = db;
        setLayout(new GridBagLayout());
        setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        JPanel cardPanel = new JPanel();
        cardPanel.setLayout(new BoxLayout(cardPanel, BoxLayout.Y_AXIS));
        cardPanel.setBackground(Color.WHITE);
        cardPanel.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(new Color(220, 220, 220), 1, true),
                BorderFactory.createEmptyBorder(30, 40, 30, 40)
        ));

        JLabel titleLabel = new JLabel("Синхронизация данных");
        titleLabel.setFont(new Font("SansSerif", Font.BOLD, 18));
        titleLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        JLabel descLabel = new JLabel("<html><center>Сохраните текущие результаты экспериментов<br>или загрузите данные из внешнего файла.</center></html>");
        descLabel.setFont(new Font("SansSerif", Font.PLAIN, 13));
        descLabel.setForeground(new Color(100, 100, 100));
        descLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        Dimension buttonSize = new Dimension(220, 40);

        JButton btnExport = new JButton("📤 Экспорт в CSV");
        btnExport.setMaximumSize(buttonSize);
        btnExport.setPreferredSize(buttonSize);
        btnExport.setAlignmentX(Component.CENTER_ALIGNMENT);
        btnExport.setFocusPainted(false);
        btnExport.addActionListener(e -> exportToCsv());

        JButton btnImport = new JButton("📥 Импорт из CSV");
        btnImport.setMaximumSize(buttonSize);
        btnImport.setPreferredSize(buttonSize);
        btnImport.setAlignmentX(Component.CENTER_ALIGNMENT);
        btnImport.setFocusPainted(false);
        btnImport.addActionListener(e -> importFromCsv());

        cardPanel.add(titleLabel);
        cardPanel.add(Box.createVerticalStrut(10));
        cardPanel.add(descLabel);
        cardPanel.add(Box.createVerticalStrut(30)); 
        cardPanel.add(btnExport);
        cardPanel.add(Box.createVerticalStrut(15)); 
        cardPanel.add(btnImport);

        add(cardPanel);
    }

    private void exportToCsv() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setFileFilter(new FileNameExtensionFilter("CSV Files", "csv"));
        if (fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            if (!file.getName().toLowerCase().endsWith(".csv")) {
                file = new File(file.getParentFile(), file.getName() + ".csv");
            }
            try (PrintWriter writer = new PrintWriter(new FileWriter(file))) {
                writer.println("Model,F1,Precision,Recall,Accuracy,Time");
                for (Experiment e : db.getAllExperiments()) {
                    writer.printf("%s,%.3f,%.3f,%.3f,%.3f,%d%n",
                            e.getModelName(), e.getF1(), e.getPrecision(),
                            e.getRecall(), e.getAccuracy(), e.getTrainingTime());
                }
                JOptionPane.showMessageDialog(this, "Экспорт успешно завершен!");
            } catch (IOException ex) {
                JOptionPane.showMessageDialog(this, "Ошибка записи: " + ex.getMessage(), "Ошибка", JOptionPane.ERROR_MESSAGE);
            }
        }
    }

    private void importFromCsv() {
        JFileChooser fileChooser = new JFileChooser();
        fileChooser.setFileFilter(new FileNameExtensionFilter("CSV Files", "csv"));
        if (fileChooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION) {
            File file = fileChooser.getSelectedFile();
            int count = 0;
            try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
                String line = reader.readLine(); 
                while ((line = reader.readLine()) != null) {
                    String[] parts = line.split(",");
                    if (parts.length >= 6) {
                        db.addExperiment(
                                parts[0], Double.parseDouble(parts[1]), Double.parseDouble(parts[2]),
                                Double.parseDouble(parts[3]), Double.parseDouble(parts[4]), Integer.parseInt(parts[5])
                        );
                        count++;
                    }
                }
                JOptionPane.showMessageDialog(this, "Успешно импортировано " + count + " записей!");
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Ошибка чтения или неверный формат: " + ex.getMessage(), "Ошибка", JOptionPane.ERROR_MESSAGE);
            }
        }
    }
}