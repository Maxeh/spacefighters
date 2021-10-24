#include "Collision.hpp"

Collision::Collision(float x, float y, int phase) :
    x(x), y(y), phase(phase) {}

float Collision::getX() const {

    return x;
}

float Collision::getY() const {

    return y;
}

void Collision::updatePhase() {

    if (++ticks == MAX_TICKS) {
        phase++;
        ticks = 0;
    }
}

float* Collision::getCords() {

    return POSITIONS[phase];
}

bool Collision::isMaxPhase() {

    return phase == sizeof(POSITIONS) / sizeof(POSITIONS[0]);
}


