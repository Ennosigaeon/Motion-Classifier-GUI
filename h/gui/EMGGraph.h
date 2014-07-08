#ifndef EMGGRAPH_H
#define EMGGRAPH_H

#include "EMGChannel.h"

#include <QWidget>
#include <qwt_plot.h>

class EMGGraph : public QWidget{
    Q_OBJECT

private:
    int nrChannels;
    int maxDisplay;
    QwtPlot *plot;
    void initComponents();
    QList<EMGChannel*> channels;

public:
    EMGGraph(int nrChannels, int maxDisplay, QWidget *parent = NULL);
    ~EMGGraph();

    void setNrChannels(int nrChannels);
    QList<EMGChannel*>* getChannels();
    void replot();

};

#endif // EMGGRAPH_H

