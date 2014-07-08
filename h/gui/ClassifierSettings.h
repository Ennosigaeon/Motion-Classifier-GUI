#ifndef CLASSIFIERSETTINGS_H
#define CLASSIFIERSETTINGS_H

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <Properties.h>
#include <Classifier.h>
#include "PropertiesLayout.h"

class ClassifierSettings : public QWidget {
    Q_OBJECT

private:
    motion_classifier::Classifier *classifier = NULL;
    Properties *prop = NULL;
    QLabel *nameLabel;
    PropertiesLayout *settingsLayout;

    void initComponents();

private slots:
    void startClicked();
    void stopClicked();
    void saveClicked();

public:
    ClassifierSettings();
    ~ClassifierSettings();

    void setClassifier(std::string name, Properties *prop);

};

#endif // CLASSIFIERSETTINGS_H
