
#include "../../h/training/MovementTrainer.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>


MovementTrainer::MovementTrainer(QWidget *parent) : QWidget(parent) {
    //setStyleSheet("background-color: blue");
    setMinimumSize(100, 100);
}

MovementTrainer::~MovementTrainer() {

}

void MovementTrainer::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1));
    QLine xAxis(width() / 2, 0, width() / 2, height());
    QLine yAxis(0, height() / 2, width(), height() / 2);
    painter.drawLine(xAxis);
    painter.drawLine(yAxis);
}
