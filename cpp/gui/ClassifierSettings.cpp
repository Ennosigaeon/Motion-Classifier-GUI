#include "../../h/gui/ClassifierSettings.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <SVMClassifier.h>

ClassifierSettings::ClassifierSettings(RealTimeProvider *provider) {
    ClassifierSettings::provider = provider;
    initComponents();
}

ClassifierSettings::~ClassifierSettings() {
    if (classifier != NULL)
        delete classifier;
    if (prop != NULL)
        delete prop;
}

//TODO: It is only possible to set a Classifier once per run. Second call will cause
//error
void ClassifierSettings::setClassifier(ClassifierEnum cl, Properties *prop) {
    if (ClassifierSettings::classifier != NULL)
        delete classifier;
    if (ClassifierSettings::prop != NULL)
        delete prop;

    ClassifierSettings::prop = prop;
    ClassifierSettings::cl = cl;

    hide();
    delete nameLabel;
    delete save;
    delete start;
    delete stop;
    if (settingsLayout != NULL)
        delete settingsLayout;
    settingsLayout = NULL;
    delete layout();
    initComponents();
    show();

    std::string s;
    switch (cl) {
    case SVM: s = "Support Vector Machine";
        break;
    default: s = "<unknown>";
    }
    nameLabel->setText(QString::fromStdString(s));
}

void ClassifierSettings::initComponents() {
    QVBoxLayout *rootLayout = new QVBoxLayout(this);

    nameLabel = new QLabel("<unknown>");
    rootLayout->addWidget(nameLabel);

    save = new QPushButton("Save");
    rootLayout->addWidget(save);

    if (prop != NULL) {
        settingsLayout = new PropertiesLayout(prop);
        rootLayout->addLayout(settingsLayout);
    }

    start = new QPushButton("Start");
    stop = new QPushButton("Stop");
    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(start);
    buttons->addWidget(stop);
    rootLayout->addLayout(buttons);
    setLayout(rootLayout);
}

void ClassifierSettings::startClicked() {
    saveClicked();

    //TODO: start classifier
}

void ClassifierSettings::stopClicked() {

}

void ClassifierSettings::saveClicked() {
    if (prop == NULL)
        return;

    settingsLayout->storeValues();
    prop->store();

    delete classifier;

    switch (cl) {
    case ClassifierEnum::SVM:
        motion_classifier::MultiClassSVM *svm = new motion_classifier::MultiClassSVM(prop);
        classifier = new motion_classifier::SVMClassifier(provider, svm, prop);
        break;
    }
}
