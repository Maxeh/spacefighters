#include "Monster.hpp"

Monster::Monster(float x, float y) :
    x(x), y(y) {}

float* Monster::getSpritePositions() {

    return SPRITE_POSITIONS[state];
}

float Monster::getX() const {

    return x;
}

float Monster::getY() const {

    return y;
}

bool Monster::isDestroyed() const {

    return destroyed;
}

void Monster::setDestroyed(bool _destroyed) {

    destroyed = _destroyed;
}

void Monster::updateState() {

    if (++ticks == MAX_TICKS) {
        state = state == 1 ? 0 : 1;
        ticks = 0;
    }
}


