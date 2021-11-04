#include "Spaceship.hpp"

Spaceship::Spaceship(float x, float y) :
    x(x), y(y) {}

float Spaceship::getX() const {

    return x;
}

void Spaceship::setX(float x_) {

    x = x_;
}

void Spaceship::moveX(float x_) {

    x += x_;
}

float Spaceship::getY() const {

    return y;
}

int Spaceship::getHealth() const {

    return health;
}

void Spaceship::setHealth(int _health) {

    Spaceship::health = _health;
}

int Spaceship::getEnergy() const {

    return energy;
}

bool Spaceship::isReloading() {

    return reloadTime.getElapsedTime().asMilliseconds() < RELOAD_TIME;
}

void Spaceship::reload() {

    reloadTime.restart();
}

float Spaceship::getVelocity() const {

    return velocity;
}

void Spaceship::resetVelocity() {

    Spaceship::velocity = DEFAULT_VELOCITY;
}

void Spaceship::accelerate() {

    if (Spaceship::velocity < Spaceship::MAX_VELOCITY) {
        Spaceship::velocity += 1;
    }
}

bool Spaceship::isMovingLeft() const {

    return movingLeft;
}

void Spaceship::setMovingLeft(bool _movingLeft) {

    Spaceship::movingLeft = _movingLeft;
}

bool Spaceship::isMovingRight() const {

    return movingRight;
}

void Spaceship::setMovingRight(bool _movingRight) {

    Spaceship::movingRight = _movingRight;
}