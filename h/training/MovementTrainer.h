#ifndef MOVEMENTTRAINER_H
#define MOVEMENTTRAINER_H

#include <QWidget>

class MovementTrainer : public QWidget {

private:

public:
    MovementTrainer(QWidget *parent = NULL);
    ~MovementTrainer();

    void paintEvent(QPaintEvent *event);
};

#endif // MOVEMENTTRAINER_H
