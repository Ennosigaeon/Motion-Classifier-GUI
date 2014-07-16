#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <string>
#include <QPaintDevice>

class Movement {
private:
    std::string name;
    std::string description;
    double translationX = 0;
    double translationY = 0;
    double rotation = 0;
    double compression = 0;

    double normalize(double number);

public:
    Movement(std::string name, std::string description, double translationX, double translationY,
             double rotation, double compression);

    std::string getName() const;

    std::string getDescription() const;

    double getTranslationX() const;

    double getTranslationY() const;

    double getRotation() const;

    double getCompression() const;
};

#endif // MOVEMENT_H
