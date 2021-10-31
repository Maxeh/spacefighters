#ifndef SPACEFIGHTERS_ASTEROID_HPP
#define SPACEFIGHTERS_ASTEROID_HPP

class Asteroid {
    float x;
    float y;
    float angle;
    float rotation;
    float velocity = 2;
    bool visible = true;
public:
    explicit Asteroid(float x, float y, float rotation);
    void rotate();
    void move();
    float getX() const;
    float getY() const;
    float getRotation() const;
    bool isVisible() const;
    void setVisible(bool _visible);
};

#endif