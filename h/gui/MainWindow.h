#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <EMGProvider.h>
#include "EMGGraph.h"
#include "ConfigurationWindow.h"
#include "ClassifierSettings.h"
#include "../training/TrainingsPainter.h"
#include "../training/TrainingsController.h"
#include "../RealTimeProvider.h"

#include <boost/filesystem.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    static const std::string CONF_FILE;
    static const std::string CACHE_FILE;
    static const std::string TRAINER_FOLDER;

    Ui::MainWindow *ui;
    QTextEdit *logText;

    Properties *cache = NULL;
    EMGGraph *emgGraph = NULL;
    RealTimeProvider *provider = NULL;
    ConfigurationWindow *configuration = NULL;
    ClassifierSettings *classifierSettings = NULL;
    TrainingsController *trainController = NULL;
    TrainingsProcedure *training = NULL;
    boost::filesystem::path *rootPath;
    QMenu *trainingsSelection;

    void initFileSystem();
    void initComponents();
    void initMenu();
    void initToolbar();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //Logs the given text to the log panel.
    void log(std::string text);

    void initTrainingsMenu();

    std::string CLASSIFIER_FOLDER = "classifier/";


private slots:
    void readingStartClicked();
    void readingStopClicked();
    void cMenuSVMClicked();
    void cMenuSMClicked();
    void eMenuFileClicked();
    void eMenuOTClicked();
    void startTrainingClicked();
    void addTrainingClicked();

public slots:
    void trainingSelected(int index);
};

#endif // MAINWINDOW_H
