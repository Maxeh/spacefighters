#ifndef SFML1_ASTEROID_HPP
#define SFML1_ASTEROID_HPP

class Asteroid {
    int x;
    int y;
    float initialRotation;
    float currentRotation;
public:
    Asteroid(int x, int y, float rotation) : x(x), y(y), initialRotation(rotation), currentRotation(rotation) {};
    int getX() const;
    int getY() const;
    float getRotation() const;
    void rotate();
    void moveX(int x);
    void moveY(int y);
};

#endif