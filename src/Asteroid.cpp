#include "Asteroid.hpp"

int Asteroid::getX() {
    return x;
}

int Asteroid::getY() {
    return y;
}

void Asteroid::moveX(int x) {
    this->x += x;
}

void Asteroid::moveY(int y) {
    this->y += y;
}