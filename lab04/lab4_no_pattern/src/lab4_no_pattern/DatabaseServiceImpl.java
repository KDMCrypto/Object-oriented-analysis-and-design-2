package lab4_no_pattern;
import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DatabaseServiceImpl implements IDatabaseService {
    private Connection connection;
    private List<Runnable> listeners = new ArrayList<>();

    public DatabaseServiceImpl() {
        try {
            connection = DriverManager.getConnection("jdbc:sqlite:mltracker.db");
            createTable();
            if (getAllExperiments().isEmpty()) insertSampleData();
        } catch (SQLException e) { e.printStackTrace(); }
    }

    private void createTable() throws SQLException {
        try (Statement stmt = connection.createStatement()) {
            stmt.execute("CREATE TABLE IF NOT EXISTS experiments (" +
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, " +
                    "name TEXT, f1 REAL, p REAL, r REAL, acc REAL, time INTEGER)");
        }
    }

    private void insertSampleData() {
        addExperiment("YOLOv8s", 0.82, 0.85, 0.79, 0.88, 1450);
        addExperiment("RT-DETR-L", 0.91, 0.93, 0.89, 0.94, 3200);
        addExperiment("Faster R-CNN", 0.75, 0.78, 0.72, 0.80, 5600);
    }

    @Override
    public List<Experiment> getAllExperiments() {
        List<Experiment> list = new ArrayList<>();
        try (Statement stmt = connection.createStatement();
             ResultSet rs = stmt.executeQuery("SELECT * FROM experiments")) {
            while (rs.next()) {
                list.add(new Experiment(rs.getInt("id"), rs.getString("name"),
                        rs.getDouble("f1"), rs.getDouble("p"), rs.getDouble("r"),
                        rs.getDouble("acc"), rs.getInt("time")));
            }
        } catch (SQLException e) { e.printStackTrace(); }
        return list;
    }

    @Override
    public void addExperiment(String name, double f1, double p, double r, double acc, int time) {
        String sql = "INSERT INTO experiments(name, f1, p, r, acc, time) VALUES(?,?,?,?,?,?)";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, name); ps.setDouble(2, f1); ps.setDouble(3, p);
            ps.setDouble(4, r); ps.setDouble(5, acc); ps.setInt(6, time);
            ps.executeUpdate();
            notifyListeners(); // Оповещаем UI
        } catch (SQLException e) { e.printStackTrace(); }
    }

    @Override
    public void updateExperiment(int id, String name, double f1, double p, double r, double acc, int time) {
        String sql = "UPDATE experiments SET name=?, f1=?, p=?, r=?, acc=?, time=? WHERE id=?";
        try (PreparedStatement ps = connection.prepareStatement(sql)) {
            ps.setString(1, name);
            ps.setDouble(2, f1);
            ps.setDouble(3, p);
            ps.setDouble(4, r);
            ps.setDouble(5, acc);
            ps.setInt(6, time);
            ps.setInt(7, id);
            ps.executeUpdate();
            
            notifyListeners(); // Оповещаем всех (графики, таблицу, аналитику)
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void deleteExperiment(int id) {
        try (PreparedStatement ps = connection.prepareStatement("DELETE FROM experiments WHERE id = ?")) {
            ps.setInt(1, id);
            ps.executeUpdate();
            notifyListeners(); // Оповещаем UI
        } catch (SQLException e) { e.printStackTrace(); }
    }

    @Override
    public void addChangeListener(Runnable listener) {
        listeners.add(listener);
    }

    private void notifyListeners() {
        for (Runnable r : listeners) r.run();
    }
}