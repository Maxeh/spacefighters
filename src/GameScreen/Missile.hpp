#ifndef SPACEFIGHTERS_MISSILE_HPP
#define SPACEFIGHTERS_MISSILE_HPP

enum class MissileDirection {UP, DOWN};

class Missile {
    float x;
    float y;
    float width = 5;
    float height = 5;
    float velocity = 5;
    bool visible = true;
    MissileDirection missileDirection;
public:
    Missile(float x, float y, MissileDirection missileDirection);
    ~Missile() = default;
    void move();
    float getX() const;
    float getY() const;
    MissileDirection getMissileDirection() const;
    float getWidth() const;
    float getHeight() const;
    bool isVisible() const;
    void setVisible(bool visible_);
};

#endif