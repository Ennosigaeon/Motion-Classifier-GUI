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

void RealTimeProvider::setClassifierActive(bool status) {
    classifierActive = status;
}

void RealTimeProvider::send(const Signal &signal){
    if (signal == Signal::START) {
        if (status == Status::NEW) {
            status = Status::RUNNING;
            if (emgProvider != NULL)
                thread = std::thread(&RealTimeProvider::run, this);
            else
                thread = std::thread(&RealTimeProvider::rndRun, this);
        }
    }
    if (signal == Signal::STOP && emgProvider != NULL)
        emgProvider->send(signal);
    if (signal == Signal::SHUTDOWN) {
        status = Status::FINISHED;
        //release lock
        if (emgProvider != NULL)
            emgProvider->send(Signal::START);
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
    emgProvider->send(Signal::START);
    channels = graph->getChannels();
    while (status == Status::RUNNING) {
        Interval *interval = emgProvider->getInterval();
        Sample *mean = interval->getMeanSample();
        math::Vector *values = mean->getEntries();
        int i = 0;
        for (QList<EMGChannel*>::iterator it = channels->begin(); it != channels->end(); ++it, ++i)
            (*it)->addValue(values[i].get(math::Dimension::Z) / 100);

        graph->replot();

        //adds the Interval to queue, so that waiting classifier can process Interval
        if (classifierActive)
            addInterval(interval);
    }
}

void RealTimeProvider::rndRun() {
    channels = graph->getChannels();
    while (status == Status::RUNNING) {
        for (auto it = channels->begin(); it != channels->end(); ++it) {
            if (((double) rand() / (RAND_MAX)) < 0.5)
                (*it)->addValue(-((double) rand() / (RAND_MAX)) / 4);
            else
                (*it)->addValue(((double) rand() / (RAND_MAX)) / 4);
        }
        graph->replot();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

