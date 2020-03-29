#include "Spaceship.hpp"

Spaceship::Spaceship(float x) : x(x) {}

void Spaceship::moveX(float x) {
    this->x += x;
}

float Spaceship::getX() const {
    return x;
}

void Spaceship::setX(float x) {
    this->x = x;
}