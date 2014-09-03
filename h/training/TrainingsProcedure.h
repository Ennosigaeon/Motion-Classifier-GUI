#ifndef TRAININGSPROCEDURE_H
#define TRAININGSPROCEDURE_H

#include <EMGProvider.h>
#include <QTimer>
#include "Movement.h"
#include "TrainingsPainter.h"
#include "../RealTimeProvider.h"

class TrainingsProcedure : public QWidget {
    Q_OBJECT

private:
    std::string name;
    int nr;
    std::vector<Movement*> movements;
    std::vector<Movement*>::const_iterator it;
    RealTimeProvider *emg;
    QTimer *timer = NULL;

private slots:

    void animate();

public:
    TrainingsProcedure(std::string name, std::vector<Movement*> movements, int nr);

    void run(RealTimeProvider *provider);

    std::string getName();

    int getNr();

    std::vector<Movement*>* getMovements();

    void paintEvent(QPaintEvent *event);
};

#endif // TRAININGSPROCEDURE_H
