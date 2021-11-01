#ifndef SPACEFIGHTERS_COLLISION_HPP
#define SPACEFIGHTERS_COLLISION_HPP

#include "Missile.hpp"

class Collision {
    int MAX_TICKS = 2;
    float SPRITE_POSITIONS[12][2] = {
        {90, 62}, {60, 62}, {30, 62}, {0, 62},
        {90, 32}, {60, 32}, {30, 32}, {0, 32},
        {90, 0}, {60, 0}, {30, 0}, {0, 0}};
    float x;
    float y;
    int state = 0;
    int ticks = 0;
    MissileDirection missileDirection;
public:
    static constexpr float COLLISION_WIDTH = 30;
    static constexpr float COLLISION_HEIGHT = 26;

    explicit Collision(float x, float y, MissileDirection missileDirection);
    float getX() const;
    float getY() const;
    MissileDirection getMissileDirection() const;
    float* getSpritePositions();
    void updateState();
    bool isMaxState();
};

#endif