#include "Asteroid.hpp"

Asteroid::Asteroid(int x, int y, float v, float rotation)
    : x(x), y(y), velocity(v), angle(rotation), rotation(rotation) {}

void Asteroid::rotate() {

    rotation += angle;
}

void Asteroid::move() {
    
    this->x += velocity;
}

int Asteroid::getX() const {
    
    return x;
}

int Asteroid::getY() const {
    
    return y;
}

float Asteroid::getRotation() const {
    
    return rotation;
}

float Asteroid::getAngle() const {

    return angle;
}

void Asteroid::setVisible(bool visible) {

    this->visible = visible;
}

bool Asteroid::isVisible() {

    return visible;
}


