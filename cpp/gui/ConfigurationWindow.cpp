#include "../../h/gui/ConfigurationWindow.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <AppConfig.h>


#include <iostream>

ConfigurationWindow::ConfigurationWindow(Properties *properties, EMGGraph *graph) {
    ConfigurationWindow::properties = properties;
    ConfigurationWindow::graph = graph;
    initComponents();

    setWindowTitle("Configurations");
    setWindowFlags(Qt::WindowTitleHint);
}

void ConfigurationWindow::initComponents() {
    QVBoxLayout *rootLayout = new QVBoxLayout();
    if (properties != NULL) {
        pl = new PropertiesLayout(properties);
        rootLayout->addLayout(pl);
    }
    QPushButton *close = new QPushButton("Close");
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(makeHidden()));
    rootLayout->addWidget(close);
    this->setLayout(rootLayout);
}

Properties* ConfigurationWindow::getProperties() {
    return properties;
}

void ConfigurationWindow::makeVisible() {
    this->show();
}

void ConfigurationWindow::makeHidden() {
    pl->storeValues();
    properties->store();
    graph->setNrChannels(properties->getInt("sample.rows") * properties->getInt("sample.columns"));
    motion_classifier::AppConfig::load(*properties);
    this->hide();
}


