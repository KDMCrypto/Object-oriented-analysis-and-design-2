package lab4_no_pattern;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class ChartsPanel extends JPanel {
    private IDatabaseService db;
    private JTabbedPane chartsTabPane = new JTabbedPane();
    private MetricsChartPanel metricsPanel = new MetricsChartPanel();
    private TimeChartPanel timePanel = new TimeChartPanel();

    private static final int METRICS_BAR_WIDTH = 30;
    private static final int METRICS_BAR_SPACING = 20;
    private static final int METRICS_FACET_MARGIN = 80;
    private static final int TIME_BAR_WIDTH = 60;
    private static final int TIME_BAR_SPACING = 60;

    public ChartsPanel(IDatabaseService db) {
        this.db = db;
        setLayout(new BorderLayout());
        setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        JScrollPane metricsScrollPane = new JScrollPane(metricsPanel);
        JScrollPane timeScrollPane = new JScrollPane(timePanel);
        metricsScrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
        timeScrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
        
        chartsTabPane.addTab("Метрики (0-1)", metricsScrollPane);
        chartsTabPane.addTab("Время обучения", timeScrollPane);

        add(chartsTabPane, BorderLayout.CENTER);
    }
    
    public void updateData() { 
        updatePanelSizes();
        metricsPanel.repaint(); 
        timePanel.repaint();
    }
    
    private void updatePanelSizes() {
        if (db == null) return;
        int expCount = db.getAllExperiments().size();
        
        int facetContentWidth = (METRICS_BAR_WIDTH + METRICS_BAR_SPACING) * expCount;
        int metricsWidth = 4 * (METRICS_FACET_MARGIN + facetContentWidth) + 3 * METRICS_FACET_MARGIN + 100;
        metricsPanel.setPreferredSize(new Dimension(metricsWidth, 600));
        
        int timeWidth = 80 + (expCount * (TIME_BAR_WIDTH + TIME_BAR_SPACING)) + 100;
        timePanel.setPreferredSize(new Dimension(timeWidth, 400));
    }

    private List<Experiment> getSortedExperiments() {
        if (db == null) return new java.util.ArrayList<>();
        return db.getAllExperiments().stream()
                .sorted(Comparator.comparingDouble(Experiment::getF1).reversed())
                .collect(Collectors.toList());
    }

    private class MetricsChartPanel extends JPanel {
        private final Color[] colors = {
            new Color(90, 150, 255), new Color(110, 230, 130), 
            new Color(255, 180, 70), new Color(180, 110, 255)
        };
        private final String[] metricNames = {"F1 Score", "Precision", "Recall", "Accuracy"};

        public MetricsChartPanel() { setBackground(Color.WHITE); }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            List<Experiment> list = getSortedExperiments();
            if (list.isEmpty()) return;

            Graphics2D g2 = (Graphics2D) g;
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int h = getHeight();
            int paddingY = 80;
            int chartH = h - paddingY * 2;
            int facetWidth = (METRICS_BAR_WIDTH + METRICS_BAR_SPACING) * list.size();

            for (int m = 0; m < 4; m++) {
                int facetStartX = METRICS_FACET_MARGIN + (m * (facetWidth + METRICS_FACET_MARGIN + 40));
                
                g2.setColor(new Color(200, 200, 200));
                for (int i = 0; i <= 10; i++) {
                    double val = i / 10.0;
                    int y = paddingY + chartH - (int) (chartH * val);
                    g2.drawLine(facetStartX, y, facetStartX + facetWidth, y);
                    g2.setColor(Color.BLACK);
                    g2.setFont(new Font("SansSerif", Font.PLAIN, 10));
                    g2.drawString(String.format("%.1f", val), facetStartX - 30, y + 4);
                    g2.setColor(new Color(200, 200, 200));
                }
                
                g2.setColor(Color.BLACK);
                g2.drawLine(facetStartX, paddingY, facetStartX, paddingY + chartH);
                g2.drawLine(facetStartX, paddingY + chartH, facetStartX + facetWidth, paddingY + chartH);

                g2.setColor(Color.BLACK);
                g2.setFont(new Font("SansSerif", Font.BOLD, 13));
                FontMetrics fm = g2.getFontMetrics();
                int titleW = fm.stringWidth(metricNames[m]);
                g2.drawString(metricNames[m], facetStartX + (facetWidth - titleW) / 2, paddingY - 25);

                for (int i = 0; i < list.size(); i++) {
                    Experiment ex = list.get(i);
                    double val = (m == 0) ? ex.getF1() : (m == 1) ? ex.getPrecision() : (m == 2) ? ex.getRecall() : ex.getAccuracy();

                    int barH = (int) (chartH * val);
                    int x = facetStartX + 15 + (i * (METRICS_BAR_WIDTH + METRICS_BAR_SPACING));
                    int y = paddingY + chartH - barH;

                    g2.setColor(colors[m]);
                    g2.fillRect(x, y, METRICS_BAR_WIDTH, barH);
                    g2.setColor(colors[m].darker());
                    g2.drawRect(x, y, METRICS_BAR_WIDTH, barH);
                    
                    g2.setColor(Color.DARK_GRAY);
                    g2.setFont(new Font("SansSerif", Font.PLAIN, 9));
                    AffineTransform orig = g2.getTransform();
                    g2.translate(x + METRICS_BAR_WIDTH/2, paddingY + chartH + 55);
                    g2.rotate(-Math.PI / 4);
                    g2.drawString(ex.getModelName(), -25, 0);
                    g2.setTransform(orig);
                }
            }
        }
    }

    private class TimeChartPanel extends JPanel {
        public TimeChartPanel() { setBackground(Color.WHITE); }

        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);
            List<Experiment> list = getSortedExperiments();
            if (list.isEmpty()) return;

            Graphics2D g2 = (Graphics2D) g;
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            int maxTime = list.stream().mapToInt(Experiment::getTrainingTime).max().orElse(1);
            int padding = 80;
            int chartH = getHeight() - padding * 2;

            g2.setColor(Color.BLACK);
            g2.drawLine(padding, padding, padding, getHeight() - padding);
            g2.drawLine(padding, getHeight() - padding, getWidth() - 20, getHeight() - padding);

            for(int i = 0; i <= 5; i++) {
                int y = padding + chartH - (int)(chartH * (i / 5.0));
                int val = (int)(maxTime * (i / 5.0));
                g2.setColor(Color.LIGHT_GRAY);
                g2.drawLine(padding, y, getWidth() - 20, y);
                g2.setColor(Color.BLACK);
                g2.drawString(String.valueOf(val) + "с", padding - 50, y + 5);
            }

            int x = padding + 30;
            for (Experiment e : list) {
                int h = (int) ((double) e.getTrainingTime() / maxTime * chartH);
                int y = padding + chartH - h;

                GradientPaint gp = new GradientPaint(x, y, new Color(255, 80, 80), x, y + h, new Color(180, 40, 40));
                g2.setPaint(gp);
                g2.fillRect(x, y, TIME_BAR_WIDTH, h);

                g2.setColor(Color.BLACK);
                g2.setFont(new Font("SansSerif", Font.PLAIN, 11));
                g2.drawString(e.getModelName(), x, getHeight() - padding + 20);
                
                g2.setColor(Color.DARK_GRAY);
                g2.drawString(e.getTrainingTime() + "с", x + 5, y - 10);

                x += (TIME_BAR_WIDTH + TIME_BAR_SPACING);
            }
        }
    }
}