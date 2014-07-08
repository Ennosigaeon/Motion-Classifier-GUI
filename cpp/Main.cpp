#include "../h/gui/MainWindow.h"
#include "../h/RealTimeProvider.h"
#include <QApplication>
#include <EMGFileProvider.h>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainWindow w;
    //w.showMaximized();
    w.show();

    return a.exec();
}
