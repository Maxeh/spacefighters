#ifndef SPACEFIGHTERS_SPACESHIP_HPP
#define SPACEFIGHTERS_SPACESHIP_HPP

#include <SFML/System/Clock.hpp>

class Spaceship {
    const int RELOAD_TIME = 200;
    float x;
    float y;
    int energy = 1000;
    int health = 1000;
    int shield = 1000;
    sf::Clock reloadTime;
public:
    explicit Spaceship(float x, float y);
    void moveX(float x);
    void reload();
    bool isReloading();
    float getX() const;
    float getY() const;
    int getEnergy() const;
    int getHealth() const;
    int getShield() const;
    void setX(float x);
};

#endif