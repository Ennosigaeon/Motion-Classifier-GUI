#ifndef REALTIMEPROVIDER_H
#define REALTIMEPROVIDER_H

#include <qwt_plot.h>
#include <EMGProviderImpl.h>
#include "gui/EMGGraph.h"
#include <fstream>

using namespace motion_classifier;

class RealTimeProvider : public EMGProviderImpl {

private:
    EMGProvider *emgProvider = NULL;
    EMGGraph *graph;
    Status status = Status::NEW;
    QList<EMGChannel*> *channels;
    bool classifierActive = false;
    std::ofstream out;

    void run();

public:
    RealTimeProvider(EMGGraph *graph);
    ~RealTimeProvider();

    void setClassifierActive(bool status, std::string file);
    void setProvider(EMGProvider *provider);
    void send(const Signal &signal);

    virtual int getSampleNr() const;
};

#endif // REALTIMEPROVIDER
