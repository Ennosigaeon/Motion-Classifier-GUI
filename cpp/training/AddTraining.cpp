#include "../../h/training/AddTraining.h"
#include <boost/lexical_cast.hpp>
#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStringListModel>

AddTraining::AddTraining(TrainingsController *trainController, MainWindow *main) {
    AddTraining::main = main;
    AddTraining::trainController = trainController;

    QVBoxLayout *rootLayout = new QVBoxLayout();
    QHBoxLayout *upperLayout = new QHBoxLayout();
    QHBoxLayout *lowerLayout = new QHBoxLayout();

    name = new QLineEdit(this);
    rootLayout->addWidget(name);

    rootLayout->addLayout(upperLayout);
    rootLayout->addLayout(lowerLayout);
    this->setLayout(rootLayout);

    listView = new QListView(this);
    QStringListModel *model = new QStringListModel(listView);
    for (auto it = trainController->getAllMovements()->begin(); it != trainController->getAllMovements()->end(); ++it) {
        int count = model->rowCount();
        model->insertRow(count);
        model->setData(model->index(count), QString::fromStdString(it->first));
    }
    listView->setModel(model);
    listView->setSelectionMode(QAbstractItemView::SingleSelection);
    listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QObject::connect(listView, SIGNAL(clicked(QModelIndex)), this, SLOT(rowSelect()));
    upperLayout->addWidget(listView);

    edit = new QTextEdit(this);
    upperLayout->addWidget(edit);

    QPushButton *save = new QPushButton("Save", this);
    QPushButton *close = new QPushButton("Cancel", this);
    lowerLayout->addWidget(save);
    lowerLayout->addWidget(close);
    QObject::connect(save, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(close, SIGNAL(clicked()), this, SLOT(cancel()));
}

void AddTraining::cancel() {
    close();
}

void AddTraining::save() {
    std::vector<Movement*> vec;
    std::string text = edit->toPlainText().toStdString();
    std::stringstream ss(text);
    std::string token;
    while (std::getline(ss, token))
        vec.push_back(trainController->getMovement(token));
    trainController->addTraining(name->text().toStdString(), vec);
    close();
    main->initTrainingsMenu();
}

void AddTraining::rowSelect() {
    foreach (const QModelIndex& index, listView->selectionModel()->selectedIndexes())
        edit->append(listView->model()->data(index).toString());
}
