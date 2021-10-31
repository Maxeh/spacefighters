#ifndef SPACEFIGHTERS_COLLISION_HPP
#define SPACEFIGHTERS_COLLISION_HPP

class Collision {
    int MAX_TICKS = 3;
    float POSITIONS[12][2] = {
        {90, 62},{60, 62},{30, 62},{0, 62},
        {90, 32},{60, 32},{30, 32},{0, 32},
        {90, 0},{60, 0},{30, 0},{0, 0}};
    float x;
    float y;
    int state = 0;
    int ticks = 0;
public:
    explicit Collision(float x, float y);
    float getX() const;
    float getY() const;
    float* getSpritePositions();
    void updateState();
    bool isMaxState();
};

#endif