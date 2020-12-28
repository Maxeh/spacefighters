#ifndef SPACEFIGHTERS_ASTEROID_HPP
#define SPACEFIGHTERS_ASTEROID_HPP

class Asteroid {
    int x;
    int y;
    float angle;
    float rotation;
    float velocity;
    bool visible = true;
public:
    explicit Asteroid(int x, int y, float v, float rotation);
    void rotate();
    void move();
    int getX() const;
    int getY() const;
    float getAngle() const;
    float getRotation() const;
    void setVisible(bool visible);
    bool isVisible();
};

#endif