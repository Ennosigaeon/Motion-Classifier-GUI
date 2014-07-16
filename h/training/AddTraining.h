#ifndef ADDTRANING_H
#define ADDTRANING_H

#include <QWidget>
#include <QTextEdit>
#include <QListView>
#include <QSpinBox>
#include <QLineEdit>

#include "TrainingsController.h"
#include "../gui/MainWindow.h"

class AddTraining : public QWidget {
    Q_OBJECT

private:
    MainWindow *main;
    QLineEdit *name;
    QTextEdit *edit;
    //TODO: implement
    //QSpinBox *nrRuns;
    QListView *listView;
    TrainingsController *trainController;

private slots:
    void rowSelect();
    void cancel();
    void save();

public:
    AddTraining(TrainingsController *trainController, MainWindow *main);
};

#endif // ADDTRANING_H
