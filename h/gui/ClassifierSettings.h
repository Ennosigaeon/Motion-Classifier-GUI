#ifndef CLASSIFIERSETTINGS_H
#define CLASSIFIERSETTINGS_H

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <Properties.h>
#include <Classifier.h>
#include "PropertiesLayout.h"
#include "../RealTimeProvider.h"

enum ClassifierEnum {
    SVM
};

class ClassifierSettings : public QWidget {
    Q_OBJECT

private:
    motion_classifier::Classifier *classifier = NULL;
    Properties *prop = NULL;
    QLabel *nameLabel;
    QPushButton *start;
    QPushButton *stop;
    QPushButton *save;
    PropertiesLayout *settingsLayout = NULL;
    RealTimeProvider *provider;
    ClassifierEnum cl;

    void initComponents();

private slots:
    void startClicked();
    void stopClicked();
    void saveClicked();

public:
    ClassifierSettings(RealTimeProvider *emgProvider);
    ~ClassifierSettings();

    void setClassifier(ClassifierEnum cl, Properties *prop);

};

#endif // CLASSIFIERSETTINGS_H
