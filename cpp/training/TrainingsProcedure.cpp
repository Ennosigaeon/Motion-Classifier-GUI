#include "../../h/training/TrainingsProcedure.h"
#include <thread>
#include <QPainter>


TrainingsProcedure::TrainingsProcedure(std::string name, std::vector<Movement*> movements, int nr) {
    TrainingsProcedure::name = name;
    TrainingsProcedure::nr = nr;
    TrainingsProcedure::movements = movements;
    setMinimumSize(100, 100);
}

std::vector<Movement*>* TrainingsProcedure::getMovements() {
    return &movements;
}

void TrainingsProcedure::run(RealTimeProvider *provider) {
    emg = provider;
    it = movements.begin();

    emg->setClassifierActive(true, "C:/Tmp/realtime.txt");
    this->show();
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
        this->close();
        emg->setClassifierActive(false, "");
        return;
    }
    this->update();
    std::cout << (**it).getName() << "\t" << emg->getSampleNr() << std::endl;
    ++it;
}


void TrainingsProcedure::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1));
    QLine xAxis(width() / 2, 0, width() / 2, height());
    QLine yAxis(0, height() / 2, width(), height() / 2);
    painter.drawLine(xAxis);
    painter.drawLine(yAxis);

    if (it != movements.end()) {
        int x = width() / 2 * ((**it).getTranslationX() + 1);
        int y = height() / 2 * ((**it).getTranslationY() + 1);
        //compression has to halved, otherwise compression of -1 would lead to circle with radius 0
        int radius = 50 * ((**it).getCompression() / 2 + 1);

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
