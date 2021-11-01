#ifndef SPACEFIGHTERS_MISSILE_HPP
#define SPACEFIGHTERS_MISSILE_HPP

enum class MissileDirection {UP, DOWN};

class Missile {
private:
    static constexpr float VELOCITY = 5;
    float x;
    float y;
    bool visible = true;
    MissileDirection missileDirection;
public:
    static constexpr float MISSILE_WIDTH = 5;
    static constexpr float MISSILE_HEIGHT = 5;
    Missile(float x, float y, MissileDirection missileDirection);
    float getX() const;
    float getY() const;
    MissileDirection getMissileDirection() const;
    bool isVisible() const;
    void setVisible(bool visible_);
    void move();
};

#endif