#include "Collision.hpp"

const float Collision::SPRITE_POSITIONS[12][2] = {
    {90, 62}, {60, 62}, {30, 62}, {0, 62},
    {90, 32}, {60, 32}, {30, 32}, {0, 32},
    {90, 0}, {60, 0}, {30, 0}, {0, 0}};

Collision::Collision(float x, float y, MissileDirection missileDirection) :
    x(x), y(y), missileDirection(missileDirection) {}

float Collision::getX() const {

    return x;
}

float Collision::getY() const {

    return y;
}

MissileDirection Collision::getMissileDirection() const {

    return missileDirection;
}

const float* Collision::getSpritePositions() const {

    return SPRITE_POSITIONS[state];
}

bool Collision::isMaxState() const {

    return state == sizeof(SPRITE_POSITIONS) / sizeof(SPRITE_POSITIONS[0]);
}

void Collision::updateState() {

    if (++ticks == MAX_TICKS) {
        state++;
        ticks = 0;
    }
}


