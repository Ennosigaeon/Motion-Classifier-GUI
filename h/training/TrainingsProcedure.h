#ifndef TRAININGSPROCEDURE_H
#define TRAININGSPROCEDURE_H

#include <EMGProvider.h>
#include <QTimer>
#include "Movement.h"
#include "TrainingsPainter.h"

class TrainingsProcedure : public QObject {
    Q_OBJECT

private:
    std::string name;
    int nr;
    std::vector<Movement*> movements;
    std::vector<Movement*>::const_iterator it;
    QTimer *timer = NULL;
    TrainingsPainter *painter;

private slots:
    void animate();

public:
    TrainingsProcedure(std::string name, std::vector<Movement*> movements, int nr);

    void run(motion_classifier::EMGProvider *provider);

    std::string getName();

    int getNr();

    std::vector<Movement*>* getMovements();
};

#endif // TRAININGSPROCEDURE_H
