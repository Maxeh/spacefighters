#include "Missile.hpp"

Missile::Missile(float x, float y, MissileDirection missileDirection, MissileOwner missileOwner) :
    x(x), y(y), missileDirection(missileDirection), missileOwner(missileOwner) {}

void Missile::move() {

    float i = missileDirection == MissileDirection::UP ? 1.f : -1.f;
    y -= velocity * i;
}

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

float Missile::getWidth() const {

    return width;
}

float Missile::getHeight() const {

    return height;
}

void Missile::setVisible(bool visible_) {

    visible = visible_;
}

MissileOwner Missile::getMissileOwner() const {

    return missileOwner;
}
