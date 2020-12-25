#include <iostream>
#include "Spaceship.hpp"

Spaceship::Spaceship(float x, float y) : x(x), y(y) {}

void Spaceship::moveX(float x) {
    this->x += x;
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

void Spaceship::setX(float x) {
    this->x = x;
}

float Spaceship::getY() const {
    return y;
}

int Spaceship::getEnergy() {
    return energy;
}

int Spaceship::getHealth() {
    return health;
}

int Spaceship::getShield() {
    return shield;
}


