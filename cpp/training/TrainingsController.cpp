#include "../../h/training/TrainingsController.h"
#include <Properties.h>
#include <fstream>

const std::string TrainingsController::CONF_FILE = "movements.txt";
const std::string TrainingsController::TRAININGS_FILE = "trainings.txt";

TrainingsController::TrainingsController(std::string rootPath) {
    TrainingsController::rootPath = rootPath;
    load();
}

TrainingsController::~TrainingsController() {
    store();
    for (auto it = movements.begin(); it != movements.end(); ++it)
        delete it->second;
    for (auto it = trainings.begin(); it != trainings.end(); ++it)
        delete *it;
}

void TrainingsController::load() {
    //movements
    std::ifstream confIn(rootPath + CONF_FILE);
    if (confIn.is_open()) {
        std::string name;
        while (std::getline(confIn, name)) {
            Properties prop(rootPath + name + ".txt");
            Movement *movement = new Movement(prop.get("name"), prop.get("desc"), prop.getDouble("trans_x"),
                                          prop.getDouble("trans_y"), prop.getDouble("rotation"), prop.getDouble("compression"));
            addMovement(movement);
        }
    }
    else
        initDefault();
    confIn.close();

    //trainings
    confIn.open(rootPath + TRAININGS_FILE);
    int i = 0;
    if (confIn.is_open()) {
        std::string name;
        while (std::getline(confIn, name)) {
            std::ifstream in(rootPath + name + ".txt");
            std::string mov;
            std::vector<Movement*> vec;
            while (std::getline(in, mov))
                vec.push_back(getMovement(mov));
            in.close();
            trainings.push_back(new TrainingsProcedure(name, vec, i++));
        }
    }
    confIn.close();
}

void TrainingsController::store() {
    //movements
    std::ofstream confOut(rootPath + CONF_FILE);

    for (auto it = movements.begin(); it != movements.end(); ++it) {
        Movement *mov = it->second;
        confOut << mov->getName() << std::endl;

        std::ofstream out(rootPath + mov->getName() + ".txt");
        out << "name = " << mov->getName() << std::endl;
        out << "desc = " << mov->getDescription() << std::endl;
        out << "trans_x = " << mov->getTranslationX() << std::endl;
        out << "trans_y = " << mov->getTranslationY() << std::endl;
        out << "rotation = " << mov->getRotation() << std::endl;
        out << "compression = " << mov->getCompression() << std::endl;
        out.close();
    }
    confOut.close();

    //trainings
    confOut.open(rootPath + TRAININGS_FILE);
    for (auto it = trainings.begin(); it != trainings.end(); ++it) {
        TrainingsProcedure *train = *it;
        confOut << train->getName() << std::endl;

        std::ofstream out(rootPath + train->getName() + ".txt");
        for (auto it2 = train->getMovements()->begin(); it2 != train->getMovements()->end(); ++it2)
            out << (*it2)->getName() << std::endl;
        out.close();
    }
}

void TrainingsController::initDefault() {
    addMovement(new Movement("Rest Position", "", 0, 0, 0, 0));
    addMovement(new Movement("Wrist Flexion", "", 0, 1, 0, 0));
    addMovement(new Movement("Wrist Extension", "", 0, -1, 0, 0));
    addMovement(new Movement("Radial Deviation (r)", "Right hand", -1, 0, 0, 0));
    addMovement(new Movement("Ulnar Deviation (r)", "Right hand", 1, 0, 0, 0));
    addMovement(new Movement("Forarm Pronation (r)", "Right hand", 0, 0, -1, 0));
    addMovement(new Movement("Forarm Supination (r)", "Right hand", 0, 0, 1, 0));
    addMovement(new Movement("Radial Deviation (l)", "Left hand", 1, 0, 0, 0));
    addMovement(new Movement("Ulnar Deviation (l)", "Left hand", -1, 0, 0, 0));
    addMovement(new Movement("Forarm Pronation (l)", "Left hand", 0, 0, 1, 0));
    addMovement(new Movement("Forarm Supination (l)", "Left hand", 0, 0, -1, 0));
    addMovement(new Movement("Hand Close", "", 0, 0, 0, -1));
    addMovement(new Movement("Hand Open", "", 0, 0, 0, 1));
    store();
}

void TrainingsController::addMovement(Movement *movement) {
    //TODO: check if movement name is unique
    movements.insert(std::make_pair(movement->getName(), movement));
}

std::map<std::string, Movement*>* TrainingsController::getAllMovements() {
    return &movements;
}

Movement* TrainingsController::getMovement(std::string name) {
    auto search = movements.find(name);
    if (search == movements.end())
        return NULL;
    return search->second;
}

void TrainingsController::addTraining(std::string name, std::vector<Movement*> movements) {
    TrainingsProcedure *train = new TrainingsProcedure(name, movements, trainings.size());
    //TODO: check if training is unique
    trainings.push_back(train);
}

std::vector<TrainingsProcedure*>* TrainingsController::getAllTrainings() {
    return &trainings;
}

TrainingsProcedure* TrainingsController::getTraining(int nr) {
    return trainings.at(nr);
}
