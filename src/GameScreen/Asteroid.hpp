#ifndef SPACEFIGHTERS_ASTEROID_HPP
#define SPACEFIGHTERS_ASTEROID_HPP

class Asteroid {
    int x;
    int y;
    float initialRotation;
    float currentRotation;
    bool visible = true;
public:
    explicit Asteroid(int x, int y, float rotation);
    void rotate();
    void moveX(int x);
    int getX() const;
    int getY() const;
    float getRotation() const;
    bool setVisible(bool visible);
    bool isVisible();
};

#endif