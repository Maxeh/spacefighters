#include "Missile.hpp"

Missile::Missile(float x, float y, MissileDirection missileDirection) :
    x(x), y(y), missileDirection(missileDirection) {}

float Missile::getX() const {

    return x;
}

float Missile::getY() const {

    return y;
}

MissileDirection Missile::getMissileDirection() const {

    return missileDirection;
}

bool Missile::isVisible() const {

    return visible;
}

void Missile::setVisible(bool visible_) {

    visible = visible_;
}

void Missile::move() {

    float i = missileDirection == MissileDirection::UP ? 1.f : -1.f;
    y -= VELOCITY * i;
}
