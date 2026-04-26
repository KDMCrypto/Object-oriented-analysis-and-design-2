package lab4;

public class Experiment {
    private int id;
    private String modelName;
    private double f1, precision, recall, accuracy;
    private int trainingTime;

    public Experiment(int id, String modelName, double f1, double precision, double recall, double accuracy, int trainingTime) {
        this.id = id;
        this.modelName = modelName;
        this.f1 = f1;
        this.precision = precision;
        this.recall = recall;
        this.accuracy = accuracy;
        this.trainingTime = trainingTime;
    }

    public int getId() { return id; }
    public String getModelName() { return modelName; }
    public double getF1() { return f1; }
    public double getPrecision() { return precision; }
    public double getRecall() { return recall; }
    public double getAccuracy() { return accuracy; }
    public int getTrainingTime() { return trainingTime; }

    @Override
    public String toString() {
        return String.format("#%d - %s", id, modelName);
    }
}