#ifndef SPACEFIGHTERS_SPACESHIP_HPP
#define SPACEFIGHTERS_SPACESHIP_HPP

class Spaceship {
    int x;
public:
    explicit Spaceship(int x) : x(x) {};
    void moveX(float x);
    void setX(float x);
    float getX() const;
};

#endif