#ifndef REALTIMEPROVIDER_H
#define REALTIMEPROVIDER_H

#include <qwt_plot.h>
#include <EMGProviderImpl.h>
#include "gui/EMGGraph.h"

using namespace motion_classifier;

class RealTimeProvider : public EMGProviderImpl {

private:
    EMGProvider *emgProvider = NULL;
    EMGGraph *graph;
    Status status = Status::NEW;
    QList<EMGChannel*> *channels;
    bool classifierActive = false;


    void run();
    //produces every 50ms a random dataset
    void rndRun();

public:
    RealTimeProvider(EMGGraph *graph);
    ~RealTimeProvider();

    void setClassifierActive(bool status);
    void setProvider(EMGProvider *provider);
    void send(const Signal &signal);
};

#endif // REALTIMEPROVIDER
