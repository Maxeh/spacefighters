#include "Asteroid.hpp"

Asteroid::Asteroid(float x, float y, float v, float rotation) :
    x(x), y(y), velocity(v), angle(rotation), rotation(rotation) {}

void Asteroid::rotate() {

    rotation += angle;
}

void Asteroid::move() {

    this->x += velocity;
}

float Asteroid::getX() const {

    return x;
}

float Asteroid::getY() const {

    return y;
}

float Asteroid::getRotation() const {

    return rotation;
}

float Asteroid::getAngle() const {

    return angle;
}

void Asteroid::setVisible(bool _visible) {

    this->visible = _visible;
}

bool Asteroid::isVisible() {

    return visible;
}


