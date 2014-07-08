#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QWidget>
#include <Properties.h>
#include "PropertiesLayout.h"
#include "EMGGraph.h"

class ConfigurationWindow : public QWidget {
    Q_OBJECT

private:
    Properties *properties;
    PropertiesLayout *pl;
    EMGGraph *graph;
    void initComponents();

public:
    ConfigurationWindow(Properties *properties, EMGGraph *graph);

    Properties* getProperties();

public slots:
    void makeVisible();
    void makeHidden();
};

#endif // CONFIGURATIONWINDOW_H
