#ifndef SPACEFIGHTERS_MISSILE_HPP
#define SPACEFIGHTERS_MISSILE_HPP

class Missile {
    float x;
    float y;
    float width = 5;
    float height = 5;
    float velocity = 5;
    bool visible = true;
public:
    Missile(float x, float y);
    ~Missile() = default;
    void move();
    float getX() const;
    float getY() const;
    float getWidth() const;
    float getHeight() const;
    bool isVisible() const;
    void setVisible(bool visible_);
};

#endif