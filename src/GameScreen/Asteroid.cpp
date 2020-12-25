#include "Asteroid.hpp"

Asteroid::Asteroid(int x, int y, float rotation)
    : x(x), y(y), initialRotation(rotation), currentRotation(rotation) {}

void Asteroid::rotate() {
    
    currentRotation += initialRotation;
}

void Asteroid::moveX(int x) {
    
    this->x += x;
}

int Asteroid::getX() const {
    
    return x;
}

int Asteroid::getY() const {
    
    return y;
}

float Asteroid::getRotation() const {
    
    return currentRotation;
}

bool Asteroid::setVisible(bool visible) {

    this->visible = visible;
}

bool Asteroid::isVisible() {

    return visible;
}


