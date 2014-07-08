#include "../../h/gui/MainWindow.h"
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

#include <EMGFileProvider.h>

const std::string MainWindow::CONF_FILE = "conf.txt";
const std::string MainWindow::CACHE_FILE = "cache.txt";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    initFileSystem();
    cache = new Properties(rootPath->string() + CACHE_FILE);

    initComponents();
    initMenu();
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
    if (cache != NULL)
        delete cache;

    delete ui;
}

void MainWindow::initFileSystem() {
    std::stringstream ss;
    if (getenv("HOME") == NULL)
        ss << getenv("HOMEDRIVE") << getenv("HOMEPATH") << "/Documents/Motion-Classifier/";
    else
        ss << getenv("HOME") << "/Documents/Motion-Classifier/";
    std::string s = ss.str();
    std::replace(s.begin(), s.end(), '\\', '/');
    rootPath = new boost::filesystem::path(s);
    if (!boost::filesystem::exists(*rootPath)) {
        boost::filesystem::create_directories(*rootPath);
        boost::filesystem::create_directory(s + CLASSIFIER_FOLDER);

        std::ofstream out(s + CONF_FILE);
        out << "sample.rows = 0" << std::endl;
        out <<"sample.columns = 0" << std::endl;
        out << "interval.nrSamples = 0" << std::endl;
        out << "emgProvider.bufferWarning = 1000" << std::endl;
        out << "blockingQueue.maxWaitTime = 5000" << std::endl;
        out << "trainer.baseDir = C:/Tmp/Trainer/" << std::endl;
        out << "trainer.trainingsSize = 3000" << std::endl;
        out << "trainer.nrRuns = 1" << std::endl;
        out << "graph.maxdisplay = 50" << std::endl;
        out.close();

        out.open(s + CACHE_FILE);
        out.close();
    }
}

void MainWindow::initComponents() {
    QHBoxLayout *rootLayout = new QHBoxLayout;

    Properties *prop = new Properties(rootPath->string() + CONF_FILE);
    motion_classifier::AppConfig::load(*prop);
    emgGraph = new EMGGraph(prop->getInt("sample.rows") * prop->getInt("sample.columns"), prop->getInt("graph.maxdisplay"));
    provider = new RealTimeProvider(emgGraph);
    rootLayout->addWidget(emgGraph);
    configuration = new ConfigurationWindow(prop, emgGraph);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rootLayout->addItem(rightLayout);

    classifierSettings = new ClassifierSettings();
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
    QAction *addTraining = new QAction("Add Training", this);
    training->addAction(addTraining);
    menuBar()->addMenu(training);

    QObject::connect(settings, SIGNAL(triggered()), configuration, SLOT(makeVisible()));
    QObject::connect(fileEMG, SIGNAL(triggered()), this, SLOT(eMenuFileClicked()));
}

void MainWindow::initToolbar() {
    QToolBar *bar = new QToolBar();
    QAction *startReading = new QAction("Start", this);
    QAction *stopReading = new QAction("Stop", this);
    QAction *training = new QAction("Training", this);
    bar->addAction(startReading);
    bar->addAction(stopReading);
    bar->addSeparator();
    bar->addAction(training);
    addToolBar(bar);

    QObject::connect(startReading, SIGNAL(triggered()), this, SLOT(readingStartClicked()));
    QObject::connect(stopReading, SIGNAL(triggered()), this, SLOT(readingStopClicked()));
}

//slots
void MainWindow::readingStartClicked() {
    provider->send(Signal::START);
}

void MainWindow::readingStopClicked() {
    provider->send(Signal::STOP);
}

void MainWindow::cMenuSVMClicked() {
    //logger->info("SVM Classifier selected");
    std::string file = "svm.txt";
    //Properties *prop = new Properties(rootPath->string() + file);
    //classifierSettings
    //ClassifierSettings *cs = new ClassifierSettings("SVM Classifier", prop);
}

void MainWindow::cMenuSMClicked() {

}

void MainWindow::eMenuFileClicked() {
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
