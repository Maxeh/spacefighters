#include "Missile.hpp"

Missile::Missile(float x, float y) : x(x), y(y) {

}

void Missile::move() {

    y -= 5;

}

float Missile::getX() {

    return x;
}

float Missile::getY() {

    return y;
}

void Missile::setVisible(bool visible) {

    this->visible = visible;
}

bool Missile::isVisible() {

    return visible;
}
