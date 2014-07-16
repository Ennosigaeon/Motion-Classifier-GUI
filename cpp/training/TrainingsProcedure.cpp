#include "../../h/training/TrainingsProcedure.h"
#include <thread>

TrainingsProcedure::TrainingsProcedure(std::string name, std::vector<Movement*> movements, int nr) {
    TrainingsProcedure::name = name;
    TrainingsProcedure::nr = nr;
    TrainingsProcedure::movements = movements;
}

std::vector<Movement*>* TrainingsProcedure::getMovements() {
    return &movements;
}

void TrainingsProcedure::run(motion_classifier::EMGProvider *provider) {
    painter = new TrainingsPainter();
    painter->show();

    it = movements.begin();
    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(2000);
}

std::string TrainingsProcedure::getName() {
    return name;
}

int TrainingsProcedure::getNr() {
    return nr;
}

//slots
void TrainingsProcedure::animate() {
    if (it == movements.end()) {
        timer->stop();
        painter->close();
        return;
    }
    painter->setMovement(*it);
    painter->update();
    ++it;
}
