#include "Asteroid.hpp"

Asteroid::Asteroid(float x, float y, float rotation) :
    x(x), y(y), angle(rotation), rotation(rotation) {}

float Asteroid::getX() const {

    return x;
}

float Asteroid::getY() const {

    return y;
}

float Asteroid::getRotation() const {

    return rotation;
}

bool Asteroid::isVisible() const {

    return visible;
}

void Asteroid::setVisible(bool _visible) {

    visible = _visible;
}

void Asteroid::rotate() {

    rotation += angle;
}

void Asteroid::move() {

    x += VELOCITY;
}


