#ifndef EMGCHANNEL_H
#define EMGCHANNEL_H

#include <qwt_plot_curve.h>

class EMGChannel : public QwtPlotCurve {
private:
    int nr;
    int size;
    int currentIndex;
    double *x;
    double *y;
    bool endlessDraw = false;

public:
    EMGChannel(int nr, int size);
    ~EMGChannel();
    void addValue(double value);
};

#endif // EMGCHANNEL_H
