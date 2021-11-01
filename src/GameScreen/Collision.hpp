#ifndef SPACEFIGHTERS_COLLISION_HPP
#define SPACEFIGHTERS_COLLISION_HPP

#include "Missile.hpp"

class Collision {
private:
    static const float SPRITE_POSITIONS[12][2];
    static const int MAX_TICKS = 2;
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
    const float* getSpritePositions() const;
    bool isMaxState() const;
    void updateState();
};

#endif