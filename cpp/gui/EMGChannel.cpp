#include "../../h/gui/EMGChannel.h"

EMGChannel::EMGChannel(int nr, int size) : nr(nr), size(size) {
    x = new double[size];
    y = new double[size];
    currentIndex = 0;

    for (int i = 0; i < size; ++i) {
        x[i] = i;
        y[i] = nr;
    }

    setRawSamples(x, y, size);
}

EMGChannel::~EMGChannel() {
    delete x;
    delete y;
}

void EMGChannel::addValue(double value) {
    value = value + nr;
    if (endlessDraw) {
        //still empty buckets
        if (currentIndex != size)
            y[++currentIndex] = value;
        else {
            for (int i = 1; i < size; ++i)
                y[i - 1] = y[i];
            y[size - 1] = value;
        }
    }
    else {
        y[currentIndex] = value;
        currentIndex = ++currentIndex % size;
    }
}

