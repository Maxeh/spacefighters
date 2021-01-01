#ifndef SPACEFIGHTERS_ASTEROID_HPP
#define SPACEFIGHTERS_ASTEROID_HPP

class Asteroid {
    float x;
    float y;
    float angle;
    float rotation;
    float velocity;
    bool visible = true;
public:
    explicit Asteroid(float x, float y, float v, float rotation);
    void rotate();
    void move();
    float getX() const;
    float getY() const;
    float getAngle() const;
    float getRotation() const;
    void setVisible(bool _visible);
    bool isVisible();
};

#endif