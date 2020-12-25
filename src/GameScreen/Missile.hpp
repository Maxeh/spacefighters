#ifndef SPACEFIGHTERS_MISSILE_HPP
#define SPACEFIGHTERS_MISSILE_HPP

class Missile {

private:
//    const int LENGTH = 50;
    float x;
    float y;
    bool visible = true;
public:
    Missile(float x, float y);
    ~Missile() = default;
    void move();
    float getX();
    float getY();
    void setVisible(bool visible);
    bool isVisible();
};

#endif