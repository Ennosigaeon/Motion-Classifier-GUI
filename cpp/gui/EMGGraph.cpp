
#include "../../h/gui/EMGGraph.h"
#include <QHBoxLayout>
#include <QTimer>
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>

#include <iostream>

EMGGraph::EMGGraph(int nrChannels, int maxDisplay, QWidget *parent) : QWidget(parent) {
    EMGGraph::maxDisplay = maxDisplay;
    initComponents();
    setNrChannels(nrChannels);
}

EMGGraph::~EMGGraph() {
    for (auto it = channels.begin(); it != channels.end(); ++it)
        delete *it;
}

void EMGGraph::initComponents() {
    plot = new QwtPlot;
    plot->enableAxis(QwtPlot::xBottom, false);
    plot->setTitle("EMG Signals");

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(plot);
    setLayout(layout);
}

void EMGGraph::setNrChannels(int nrChannels) {
    if (nrChannels > maxDisplay)
        nrChannels = maxDisplay;
    this->nrChannels = nrChannels;
    plot->setAxisScale(QwtPlot::yLeft, -1, nrChannels);

    for (auto it = channels.begin(); it != channels.end(); ++it)
        delete *it;
    channels.clear();
    for (int i = 0; i < nrChannels; ++i) {
        EMGChannel *c = new EMGChannel(i, 100);
        channels.push_back(c);
        c->attach(plot);
    }
    plot->replot();
}

QList<EMGChannel*>* EMGGraph::getChannels() {
    return &channels;
}

void EMGGraph::replot() {
    plot->replot();
}

