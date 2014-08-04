#include "../../h/gui/MainWindow.h"
#include "../../h/training/AddTraining.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <sstream>

#include <QDialog>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSignalMapper>

#include <EMGFileProvider.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    config = ConfigManager::getInstance();
    trainController = new TrainingsController(config->getTrainerDir());

    initComponents();
    initMenu();
    initTrainingsMenu();
    initToolbar();
}

MainWindow::~MainWindow() {
    //delete rootPath;
    if (provider != NULL)
        delete provider;
    if (classifierSettings != NULL)
        delete classifierSettings;
    if (configuration != NULL)
        delete configuration;
    if (trainController != NULL)
        delete trainController;
    if (config != NULL)
        delete config;

    delete ui;
}

void MainWindow::initComponents() {
    QHBoxLayout *rootLayout = new QHBoxLayout;

    Properties *prop = config->getConf();
    motion_classifier::AppConfig::load(*prop);
    emgGraph = new EMGGraph(prop->getInt("sample.rows") * prop->getInt("sample.columns"), prop->getInt("graph.maxdisplay"));
    provider = new RealTimeProvider(emgGraph);
    rootLayout->addWidget(emgGraph);
    configuration = new ConfigurationWindow(prop, emgGraph);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rootLayout->addItem(rightLayout);

    classifierSettings = new ClassifierSettings(provider);
    rightLayout->addWidget(classifierSettings);

    logText = new QTextEdit;
    logText->setReadOnly(true);
    logText->setMaximumHeight(100);
    rightLayout->addWidget(logText);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(rootLayout);
    this->setCentralWidget(centralWidget);
}

void MainWindow::initMenu() {
    QMenu *file = new QMenu("Tools");
    QAction *settings = new QAction("Configuration", this);
    file->addAction(settings);
    menuBar()->addMenu(file);

    QMenu *classifier = new QMenu("Classifier");
    QAction *svmClassifier = new QAction("Support Vector Machine", this);
    QAction *smClassifier = new QAction("Mean Shift", this);
    classifier->addAction(svmClassifier);
    classifier->addAction(smClassifier);
    menuBar()->addMenu(classifier);

    QMenu *emgProvider = new QMenu("EMG Source");
    QAction *fileEMG = new QAction("File", this);
    QAction *otEMG = new QAction("OT Biolab", this);
    emgProvider->addAction(fileEMG);
    emgProvider->addAction(otEMG);
    menuBar()->addMenu(emgProvider);

    QMenu *training = new QMenu("Training");
    trainingsSelection = new QMenu("Select Training");
    training->addMenu(trainingsSelection);
    training->addSeparator();
    QAction *addTraining = new QAction("Add Training", this);
    training->addAction(addTraining);
    menuBar()->addMenu(training);

    QObject::connect(settings, SIGNAL(triggered()), configuration, SLOT(makeVisible()));
    QObject::connect(fileEMG, SIGNAL(triggered()), this, SLOT(eMenuFileClicked()));
    QObject::connect(svmClassifier, SIGNAL(triggered()), this, SLOT(cMenuSVMClicked()));
    QObject::connect(addTraining, SIGNAL(triggered()), this, SLOT(addTrainingClicked()));
}

void MainWindow::initToolbar() {
    QToolBar *bar = new QToolBar();
    QAction *startReading = new QAction("Start", this);
    QAction *stopReading = new QAction("Stop", this);
    QAction *training = new QAction("Train Classifier", this);
    bar->addAction(startReading);
    bar->addAction(stopReading);
    bar->addSeparator();
    bar->addAction(training);
    addToolBar(bar);

    QObject::connect(startReading, SIGNAL(triggered()), this, SLOT(readingStartClicked()));
    QObject::connect(stopReading, SIGNAL(triggered()), this, SLOT(readingStopClicked()));
    QObject::connect(training, SIGNAL(triggered()), this, SLOT(startTrainingClicked()));
}

void MainWindow::initTrainingsMenu() {
    trainingsSelection->clear();
    QSignalMapper *mapper = new QSignalMapper(this);
    QObject::connect(mapper, SIGNAL(mapped(int)), this, SLOT(trainingSelected(int)));

    for (auto it = trainController->getAllTrainings()->begin(); it != trainController->getAllTrainings()->end(); ++it) {
        QAction *a = new QAction(QString::fromStdString((*it)->getName()), trainingsSelection);
        trainingsSelection->addAction(a);
        mapper->setMapping(a, (*it)->getNr());
        QObject::connect(a, SIGNAL(triggered()), mapper, SLOT(map()));
    }
}

//slots
void MainWindow::readingStartClicked() {
    provider->send(Signal::START);
}

void MainWindow::readingStopClicked() {
    provider->send(Signal::STOP);
}

void MainWindow::cMenuSVMClicked() {
    std::string file = "classifier/svm.txt";
    classifierSettings->setClassifier(ClassifierEnum::SVM, new Properties(config->getRootPath() + file));
}

void MainWindow::cMenuSMClicked() {

}

void MainWindow::eMenuFileClicked() {
    Properties *cache = config->getCache();
    QFileDialog dialog(this, "File Selector", QString::fromStdString(cache->get("emgFile")));

    //only true, when user selected "Ok"
    if (dialog.exec()) {
        QStringList filenames = dialog.selectedFiles();
        if (filenames.size() == 1) {
            std::string file = filenames.at(0).toStdString();
            //cache last opened file
            cache->set("emgFile", file);
            cache->store();

            EMGFileProvider *provider = new EMGFileProvider(file);
            MainWindow::provider->setProvider(provider);
        }
        else {
            //TODO: show error
        }
    }
}

void MainWindow::eMenuOTClicked() {

}

void MainWindow::addTrainingClicked() {
    AddTraining *add = new AddTraining(trainController, this);
    add->show();
}

void MainWindow::trainingSelected(int index) {
    training = trainController->getTraining(index);
    std::cout << training->getName() << std::endl;
}

void MainWindow::startTrainingClicked() {
    if (training == NULL)
        return;
    training->run(provider);
}
