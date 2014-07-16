#ifndef TRAININGSPAINTER_H
#define TRAININGSPAINTER_H

#include <QWidget>
#include "Movement.h"

class TrainingsPainter : public QWidget {

private:
    Movement *movement = NULL;

public:
    TrainingsPainter(QWidget *parent = NULL);
    ~TrainingsPainter();

    void setMovement(Movement *movement);

    void paintEvent(QPaintEvent *event);
};

#endif // TRAININGSPAINTER_H
