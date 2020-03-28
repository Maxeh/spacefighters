//
// Created by Maximilian on 25.03.2020.
//

#include <iostream>
#include "Spaceship.hpp"

void Spaceship::moveX(float x) {
    this->x += x;
}

float Spaceship::getX() const {
    return x;
}

void Spaceship::setX(float x) {
    this->x = x;
}


