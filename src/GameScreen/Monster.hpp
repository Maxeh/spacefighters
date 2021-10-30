#ifndef SPACEFIGHTERS_MONSTER_HPP
#define SPACEFIGHTERS_MONSTER_HPP

class Monster {
    float SPRITE_POSITIONS[2][2] = { {0 ,0}, {0, 49} };
    int MAX_TICKS = 10;

    float x;
    float y;
    int state = 0;
    int ticks = 0;
    bool destroyed = false;
public:
    Monster(float x, float y);
    float* getSpritePositions();
    float getX() const;
    float getY() const;
    bool isDestroyed() const;
    void setDestroyed(bool destroyed);
    void updateState();
};

#endif
