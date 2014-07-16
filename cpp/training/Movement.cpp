#include "../../h/training/Movement.h"
#include <QPainter>

Movement::Movement(std::string name, std::string description, double translationX, double translationY,
                   double rotation, double compression) {
    Movement::name = name;
    Movement::description = description;
    Movement::translationX = normalize(translationX);
    Movement::translationY = normalize(translationY);
    Movement::rotation = normalize(rotation);
    Movement::compression = normalize(compression);
}

double Movement::normalize(double number) {
    if (number < -1)
        return -1;
    if (number > 1)
        return 1;
    return number;
}

std::string Movement::getName() const {
    return name;
}

std::string Movement::getDescription() const {
    return description;
}

double Movement::getTranslationX() const {
    return translationX;
}

double Movement::getTranslationY() const {
    return translationY;
}

double Movement::getRotation() const {
    return rotation;
}

double Movement::getCompression() const {
    return compression;
}
