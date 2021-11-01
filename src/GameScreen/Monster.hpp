#ifndef SPACEFIGHTERS_MONSTER_HPP
#define SPACEFIGHTERS_MONSTER_HPP

class Monster {
private:
    static const float SPRITE_POSITIONS[2][2];
    static const int MAX_STATE_TICKS = 20;
    static const int MAX_MOVE_TICKS = 60;
    float x;
    float y;
    int state = 0;
    int stateTicks = 0;
    int moveTicks = 0;
    bool destroyed = false;
public:
    static constexpr float MONSTER_WIDTH = 62;
    static constexpr float MONSTER_HEIGHT = 45;
    explicit Monster(float x, float y);
    float getX() const;
    float getY() const;
    const float* getSpritePositions() const;
    bool isDestroyed() const;
    void setDestroyed(bool destroyed);
    void updateState(bool right);
};

#endif
