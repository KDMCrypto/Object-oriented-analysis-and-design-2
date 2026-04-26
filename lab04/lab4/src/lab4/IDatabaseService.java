package lab4;
import java.util.List;

public interface IDatabaseService {
    List<Experiment> getAllExperiments();
    void addExperiment(String name, double f1, double p, double r, double acc, int time);
    void deleteExperiment(int id);
    void updateExperiment(int id, String name, double f1, double p, double r, double acc, int time);
    // позволяет UI и плагинам реагировать на изменения в БД
    void addChangeListener(Runnable listener);
}