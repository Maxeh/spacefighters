#include "Collision.hpp"

Collision::Collision(float x, float y, MissileDirection missileDirection) :
    x(x), y(y), missileDirection(missileDirection) {}

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

    return SPRITE_POSITIONS[state];
}

bool Collision::isMaxState() {

    return state == sizeof(SPRITE_POSITIONS) / sizeof(SPRITE_POSITIONS[0]);
}

MissileDirection Collision::getMissileDirection() const {

    return missileDirection;
}


