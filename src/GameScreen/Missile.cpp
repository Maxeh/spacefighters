#include "Missile.hpp"

Missile::Missile(float x, float y) :
    x(x), y(y) {}

void Missile::move() {

    y -= velocity;
}

float Missile::getX() const {

    return x;
}

float Missile::getY() const {

    return y;
}

bool Missile::isVisible() const {

    return visible;
}

float Missile::getWidth() const {

    return width;
}

float Missile::getHeight() const {

    return height;
}

void Missile::setVisible(bool visible_) {

    visible = visible_;
}