#ifndef SPACEFIGHTERS_SPACESHIP_HPP
#define SPACEFIGHTERS_SPACESHIP_HPP

class Spaceship {
    float x;
public:
    explicit Spaceship(float x);
    void moveX(float x);
    void setX(float x);
    float getX() const;
};

#endif