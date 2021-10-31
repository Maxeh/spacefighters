#include "Collision.hpp"

Collision::Collision(float x, float y) :
    x(x), y(y) {}

float Collision::getX() const {

    return x;
}

float Collision::getY() const {

    return y;
}

void Collision::updateState() {

    if (++ticks == MAX_TICKS) {
        state++;
        ticks = 0;
    }
}

float* Collision::getSpritePositions() {

    return POSITIONS[state];
}

bool Collision::isMaxState() {

    return state == sizeof(POSITIONS) / sizeof(POSITIONS[0]);
}


