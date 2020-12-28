#ifndef SPACEFIGHTERS_MISSILE_HPP
#define SPACEFIGHTERS_MISSILE_HPP

class Missile {
private:
    float x;
    float y;
    float width = 5;
    float height = 30;
    float velocity = 20;
    bool visible = true;
public:
    Missile(float x, float y);
    ~Missile() = default;
    void move();
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    float getSpeed();
    void setVisible(bool visible);
    bool isVisible();
};

#endif