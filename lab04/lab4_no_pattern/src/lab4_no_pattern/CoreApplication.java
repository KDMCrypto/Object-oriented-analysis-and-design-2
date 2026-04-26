package lab4_no_pattern;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;

public class CoreApplication extends JFrame {
    private IDatabaseService dbService = new DatabaseServiceImpl();
    private JTabbedPane tabbedPane = new JTabbedPane();
    private DefaultTableModel tableModel;
    
    // Прямые ссылки на панели для их обновления
    private ChartsPanel chartsPanel;
    private CsvPanel csvPanel;
    private StatsPanel statsPanel;
    
    private boolean isRefreshing = false;

    public CoreApplication() {
        try { UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName()); } 
        catch (Exception e) { /* игнорируем */ }

        setTitle("ML Experiment Analyzer Pro (Monolith)");
        setSize(1100, 750);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        // Инициализация панелей напрямую
        chartsPanel = new ChartsPanel(dbService);
        csvPanel = new CsvPanel(dbService);
        statsPanel = new StatsPanel(dbService);

        tabbedPane.addTab("База данных (CRUD)", createCrudPanel());
        tabbedPane.addTab("Аналитика", statsPanel);
        tabbedPane.addTab("Дашборд", chartsPanel);
        tabbedPane.addTab("Импорт/Экспорт CSV", csvPanel);
        
        add(tabbedPane);

        // Централизованное обновление всех панелей при изменении БД
        dbService.addChangeListener(() -> {
            refreshTable();
            chartsPanel.updateData();
            statsPanel.updateData();
        });

        // Первичная загрузка
        refreshTable();
        chartsPanel.updateData();
        statsPanel.updateData();
    }

    private JPanel createCrudPanel() {
        JPanel mainPanel = new JPanel(new BorderLayout());
        
        String[] cols = {"ID", "Модель", "F1", "Prec", "Rec", "Acc", "Время(с)"};
        tableModel = new DefaultTableModel(cols, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return column != 0; 
            }
        };
        
        JTable table = new JTable(tableModel);
        
        tableModel.addTableModelListener(e -> {
            if (isRefreshing) return; 

            if (e.getType() == javax.swing.event.TableModelEvent.UPDATE) {
                int row = e.getFirstRow();
                try {
                    int id = (int) tableModel.getValueAt(row, 0);
                    String name = tableModel.getValueAt(row, 1).toString();
                    double f1 = Double.parseDouble(tableModel.getValueAt(row, 2).toString());
                    double p = Double.parseDouble(tableModel.getValueAt(row, 3).toString());
                    double r = Double.parseDouble(tableModel.getValueAt(row, 4).toString());
                    double acc = Double.parseDouble(tableModel.getValueAt(row, 5).toString());
                    int time = Integer.parseInt(tableModel.getValueAt(row, 6).toString());

                    dbService.updateExperiment(id, name, f1, p, r, acc, time);
                    
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(this, "Ошибка формата: введите числовые значения (0.0)", "Ошибка", JOptionPane.ERROR_MESSAGE);
                    refreshTable(); 
                }
            }
        });

        JPanel inputPanel = new JPanel(new GridLayout(0, 2, 5, 5));
        inputPanel.setBorder(BorderFactory.createTitledBorder("Новая запись"));
        
        JTextField fName = new JTextField(); JTextField fF1 = new JTextField();
        JTextField fPrec = new JTextField(); JTextField fRec = new JTextField();
        JTextField fAcc = new JTextField();  JTextField fTime = new JTextField();

        inputPanel.add(new JLabel(" Название модели:")); inputPanel.add(fName);
        inputPanel.add(new JLabel(" F1 Score:")); inputPanel.add(fF1);
        inputPanel.add(new JLabel(" Precision:")); inputPanel.add(fPrec);
        inputPanel.add(new JLabel(" Recall:")); inputPanel.add(fRec);
        inputPanel.add(new JLabel(" Accuracy:")); inputPanel.add(fAcc);
        inputPanel.add(new JLabel(" Время (сек):")); inputPanel.add(fTime);

        JButton btnAdd = new JButton("Добавить эксперимент");
        btnAdd.addActionListener(e -> {
            try {
                dbService.addExperiment(
                    fName.getText(), Double.parseDouble(fF1.getText()),
                    Double.parseDouble(fPrec.getText()), Double.parseDouble(fRec.getText()),
                    Double.parseDouble(fAcc.getText()), Integer.parseInt(fTime.getText())
                );
                fName.setText(""); fF1.setText(""); fPrec.setText(""); 
                fRec.setText(""); fAcc.setText(""); fTime.setText("");
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Проверьте правильность ввода данных");
            }
        });

        JButton btnDel = new JButton("Удалить выбранное");
        btnDel.setBackground(new Color(255, 230, 230));
        btnDel.addActionListener(e -> {
            int row = table.getSelectedRow();
            if (row != -1) {
                int id = (int) tableModel.getValueAt(row, 0);
                dbService.deleteExperiment(id);
            }
        });

        JPanel buttonsPanel = new JPanel(new FlowLayout(FlowLayout.CENTER, 10, 10));
        buttonsPanel.add(btnAdd);
        buttonsPanel.add(btnDel);

        JPanel rightPanel = new JPanel(new BorderLayout());
        rightPanel.add(inputPanel, BorderLayout.NORTH);
        rightPanel.add(buttonsPanel, BorderLayout.CENTER);

        mainPanel.add(new JScrollPane(table), BorderLayout.CENTER);
        mainPanel.add(rightPanel, BorderLayout.EAST);
        
        return mainPanel;
    }

    private void refreshTable() {
        isRefreshing = true; 
        tableModel.setRowCount(0);
        dbService.getAllExperiments().forEach(ex -> 
            tableModel.addRow(new Object[]{
                ex.getId(), ex.getModelName(), ex.getF1(), 
                ex.getPrecision(), ex.getRecall(), ex.getAccuracy(), ex.getTrainingTime()
            })
        );
        isRefreshing = false; 
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new CoreApplication().setVisible(true));
    }
}