package lab4;
import javax.swing.JPanel;

public interface IPluginAPI {
    String getTabName();
    void onInitialize(IDatabaseService db);
    void onExperimentSelected(int id);
    JPanel getPanel();
}
