#include "Monster.hpp"

const float Monster::SPRITE_POSITIONS[2][2] = { {0 ,0}, {0, 49} };

Monster::Monster(float x, float y) :
    x(x), y(y) {}

float Monster::getX() const {

    return x;
}

float Monster::getY() const {

    return y;
}

const float* Monster::getSpritePositions() const {

    return SPRITE_POSITIONS[state];
}

bool Monster::isDestroyed() const {

    return destroyed;
}

void Monster::setDestroyed(bool _destroyed) {

    destroyed = _destroyed;
}

void Monster::updateState(bool monstersMovingRight) {

    if (++stateTicks == MAX_STATE_TICKS) {
        state = state == 1 ? 0 : 1;
        stateTicks = 0;
    }

    if(++moveTicks == MAX_MOVE_TICKS) {
        if (monstersMovingRight) {
            x += MONSTER_WIDTH;
        } else {
            x -= MONSTER_WIDTH;
        }
        moveTicks = 0;
    }
}