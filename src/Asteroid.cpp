#include "Asteroid.hpp"

int Asteroid::getX() const {
    return x;
}

int Asteroid::getY() const {
    return y;
}

void Asteroid::moveX(int x) {
    this->x += x;
}

void Asteroid::moveY(int y) {
    this->y += y;
}

float Asteroid::getRotation() const {
    return currentRotation;
}

void Asteroid::rotate() {

    currentRotation += initialRotation;
}