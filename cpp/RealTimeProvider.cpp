#include "../h/RealTimeProvider.h"

RealTimeProvider::RealTimeProvider(EMGGraph *graph) {
    RealTimeProvider::graph = graph;
}

RealTimeProvider::~RealTimeProvider() {
    send(Signal::SHUTDOWN);
    if (emgProvider != NULL)
        delete emgProvider;
}

void RealTimeProvider::setProvider(EMGProvider *provider) {
    if (emgProvider != NULL) {
        send(Signal::SHUTDOWN);
        delete emgProvider;
    }
    RealTimeProvider::emgProvider = provider;
}

void RealTimeProvider::setClassifierActive(bool status, std::string file) {
    if (status == classifierActive)
        return;

    classifierActive = status;

    if (classifierActive && !file.empty()) {
        out.open(file);
    }
    else {
        out.close();
    }
}

void RealTimeProvider::send(const Signal &signal){
    if (emgProvider == NULL) {
        //TODO: Show warning
        return;
    }

    if (signal == Signal::START) {
        emgProvider->send(Signal::START);
        if (status == Status::NEW) {
            status = Status::RUNNING;
            thread = std::thread(&RealTimeProvider::run, this);
        }
    }
    if (signal == Signal::STOP)
        emgProvider->send(signal);
    if (signal == Signal::SHUTDOWN) {
        status = Status::FINISHED;
        emgProvider->send(Signal::SHUTDOWN);
        if (thread.joinable())
            thread.join();
    }
}

/*
 * Sometimes a error occurs "read access violation". This happens, when
 * the Interval lenght is to small. I think the problem is that the graph
 * is reploted to fast.
 */
void RealTimeProvider::run() {
    channels = graph->getChannels();
    while (status == Status::RUNNING) {
        Interval *interval = emgProvider->getInterval();
        if (interval == NULL)
            continue;

        Sample *mean = interval->getMeanSample();
        math::Vector *values = mean->getEntries();
        int i = 0;
        for (QList<EMGChannel*>::iterator it = channels->begin(); it != channels->end(); ++it, ++i)
            (*it)->addValue(values[i].get(math::Dimension::Z) / 100);

        graph->replot();

        //adds the Interval to queue, so that waiting classifier can process Interval
        if (classifierActive) {
            if (out.is_open())
                out << *interval->getMeanSample();
            addInterval(interval);
        }
    }
}

int RealTimeProvider::getSampleNr() const {
    return emgProvider->getSampleNr();
}

