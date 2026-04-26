package lab4;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.ServiceLoader;

public class CoreApplication extends JFrame {
    private IDatabaseService dbService = new DatabaseServiceImpl();
    private List<IPluginAPI> loadedPlugins = new ArrayList<>();
    private JTabbedPane tabbedPane = new JTabbedPane();
    private DefaultTableModel tableModel;
    
    // Флаг для предотвращения рекурсии при обновлении таблицы
    private boolean isRefreshing = false;

    public CoreApplication() {
        // Устанавливаем системный стиль интерфейса
        try { UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName()); } 
        catch (Exception e) { /* игнорируем */ }

        setTitle("ML Experiment Analyzer Pro");
        setSize(1100, 750);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setLocationRelativeTo(null);

        tabbedPane.addTab("База данных (CRUD)", createCrudPanel());
        loadPlugins();
        
        add(tabbedPane);

        // Подписка на изменения в БД, любое изменение в БД обновит всё GUI
        dbService.addChangeListener(() -> {
            refreshTable();
            notifyPlugins();
        });

        // Начальная загрузка
        refreshTable();
        notifyPlugins();
    }

    private JPanel createCrudPanel() {
        JPanel mainPanel = new JPanel(new BorderLayout());
        
        // Настройка таблицы
        String[] cols = {"ID", "Модель", "F1", "Prec", "Rec", "Acc", "Время(с)"};
        tableModel = new DefaultTableModel(cols, 0) {
            @Override
            public boolean isCellEditable(int row, int column) {
                return column != 0; // ID редактировать нельзя
            }
        };
        
        JTable table = new JTable(tableModel);
        
        // Обновление ячеек
        tableModel.addTableModelListener(e -> {
            if (isRefreshing) return; // Игнорируем, если таблица сейчас заполняется программно

            if (e.getType() == javax.swing.event.TableModelEvent.UPDATE) {
                int row = e.getFirstRow();
                try {
                    // Считываем измененные данные из строки
                    int id = (int) tableModel.getValueAt(row, 0);
                    String name = tableModel.getValueAt(row, 1).toString();
                    double f1 = Double.parseDouble(tableModel.getValueAt(row, 2).toString());
                    double p = Double.parseDouble(tableModel.getValueAt(row, 3).toString());
                    double r = Double.parseDouble(tableModel.getValueAt(row, 4).toString());
                    double acc = Double.parseDouble(tableModel.getValueAt(row, 5).toString());
                    int time = Integer.parseInt(tableModel.getValueAt(row, 6).toString());

                    // Сохраняем изменения в БД
                    dbService.updateExperiment(id, name, f1, p, r, acc, time);
                    
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(this, "Ошибка формата: введите числовые значения (0.0)", "Ошибка", JOptionPane.ERROR_MESSAGE);
                    refreshTable(); // Откатываем таблицу к данным из БД
                }
            }
        });

        // Форма добавления
        JPanel inputPanel = new JPanel(new GridLayout(0, 2, 5, 5));
        inputPanel.setBorder(BorderFactory.createTitledBorder("Новая запись"));
        
        JTextField fName = new JTextField();
        JTextField fF1 = new JTextField();
        JTextField fPrec = new JTextField();
        JTextField fRec = new JTextField();
        JTextField fAcc = new JTextField();
        JTextField fTime = new JTextField();

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
                    fName.getText(),
                    Double.parseDouble(fF1.getText()),
                    Double.parseDouble(fPrec.getText()),
                    Double.parseDouble(fRec.getText()),
                    Double.parseDouble(fAcc.getText()),
                    Integer.parseInt(fTime.getText())
                );
                // Очистка полей
                fName.setText(""); fF1.setText(""); fPrec.setText(""); fRec.setText(""); fAcc.setText(""); fTime.setText("");
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
        isRefreshing = true; // Блокируем вызов TableModelListener
        tableModel.setRowCount(0);
        dbService.getAllExperiments().forEach(ex -> 
            tableModel.addRow(new Object[]{
                ex.getId(), 
                ex.getModelName(), 
                ex.getF1(), 
                ex.getPrecision(), 
                ex.getRecall(), 
                ex.getAccuracy(), 
                ex.getTrainingTime()
            })
        );
        isRefreshing = false; // Разблокируем
    }

    private void loadPlugins() {
        ServiceLoader<IPluginAPI> loader = ServiceLoader.load(IPluginAPI.class);
        for (IPluginAPI plugin : loader) {
            plugin.onInitialize(dbService);
            loadedPlugins.add(plugin);
            tabbedPane.addTab(plugin.getTabName(), plugin.getPanel());
        }
    }

    private void notifyPlugins() {
        for (IPluginAPI p : loadedPlugins) {
            p.onExperimentSelected(-1);
        }
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> new CoreApplication().setVisible(true));
    }
}