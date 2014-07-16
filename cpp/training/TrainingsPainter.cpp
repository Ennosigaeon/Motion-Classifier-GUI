
#include "../../h/training/TrainingsPainter.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>


TrainingsPainter::TrainingsPainter(QWidget *parent) : QWidget(parent) {
    //setStyleSheet("background-color: blue");
    setMinimumSize(100, 100);
}

TrainingsPainter::~TrainingsPainter() {

}

void TrainingsPainter::setMovement(Movement *movement) {
    TrainingsPainter::movement = movement;
}

void TrainingsPainter::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1));
    QLine xAxis(width() / 2, 0, width() / 2, height());
    QLine yAxis(0, height() / 2, width(), height() / 2);
    painter.drawLine(xAxis);
    painter.drawLine(yAxis);

    if (movement != NULL) {
        int x = width() / 2 * (movement->getTranslationX() + 1);
        int y = height() / 2 * (movement->getTranslationY() + 1);
        //compression has to halved, otherwise compression of -1 would lead to circle with radius 0
        int radius = 50 * (movement->getCompression() / 2 + 1);

        if (x < radius)
            x = radius;
        if (x > width() - radius)
            x = width() - radius;
        if (y < radius)
            y = radius;
        if (y > height() - radius)
            y = height() - radius;

        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(Qt::red, 5));
        painter.drawEllipse(x - radius, y - radius, radius * 2, radius * 2);
    }
}
