#ifndef TRAININGSCONTROLLER_H
#define TRAININGSCONTROLLER_H

#include "TrainingsProcedure.h"
#include "Movement.h"
#include <map>

class TrainingsController {

private:
    static const std::string CONF_FILE;
    static const std::string TRAININGS_FILE;
    std::string rootPath;
    std::map<std::string, Movement*> movements;
    std::vector<TrainingsProcedure*> trainings;

    void initDefault();
    void load();
    void store();

public:
    TrainingsController(std::string rootPath);
    ~TrainingsController();

    void addMovement(Movement* movement);

    std::map<std::string, Movement*>* getAllMovements();

    Movement* getMovement(std::string name);

    void addTraining(std::string name, std::vector<Movement*> movements);

    std::vector<TrainingsProcedure*>* getAllTrainings();

    TrainingsProcedure* getTraining(int nr);
};

#endif // TRAININGSCONTROLLER_H
