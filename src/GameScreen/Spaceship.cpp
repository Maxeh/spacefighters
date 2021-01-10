#include <iostream>
#include "Spaceship.hpp"

Spaceship::Spaceship(float x, float y) :
    x(x), y(y) {}

void Spaceship::moveX(float x_) {

    x += x_;
}

bool Spaceship::isReloading() {

    return reloadTime.getElapsedTime().asMilliseconds() < RELOAD_TIME;
}

void Spaceship::reload() {

    reloadTime.restart();
}

float Spaceship::getX() const {

    return x;
}

float Spaceship::getY() const {

    return y;
}

int Spaceship::getEnergy() const {

    return energy;
}

int Spaceship::getHealth() const {

    return health;
}

int Spaceship::getShield() const {

    return shield;
}

void Spaceship::setX(float x_) {

    x = x_;
}