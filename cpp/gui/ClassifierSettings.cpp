#include "../../h/gui/ClassifierSettings.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <SVMClassifier.h>

ClassifierSettings::ClassifierSettings() {
    initComponents();
}

ClassifierSettings::~ClassifierSettings() {
    if (classifier != NULL)
        delete classifier;
    if (prop != NULL)
        delete prop;
}

void ClassifierSettings::setClassifier(std::string name, Properties *prop) {
    if (ClassifierSettings::classifier != NULL)
        delete classifier;
    if (ClassifierSettings::prop != NULL)
        delete prop;

    ClassifierSettings::prop = prop;

    nameLabel->setText(QString::fromStdString(name));
}

void ClassifierSettings::initComponents() {
    QVBoxLayout *root = new QVBoxLayout();

    nameLabel = new QLabel("<unknown>", this);
    root->addWidget(nameLabel);

    if (prop != NULL)
        settingsLayout = new PropertiesLayout(prop);

    QPushButton *save = new QPushButton("Save");
    root->addWidget(save);

    QPushButton *start = new QPushButton("Start");
    QPushButton *stop = new QPushButton("Stop");
    QHBoxLayout *buttons = new QHBoxLayout();
    buttons->addWidget(start);
    buttons->addWidget(stop);
    root->addLayout(buttons);
    setLayout(root);
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

    if (nameLabel->text().toStdString() == "Support Vector Machine") {
        classifier = new set;
    }
    if (nameLabel->text().toStdString() == "Mean Shift") {

    }
}
