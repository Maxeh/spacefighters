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
    void setX(float x);
    float getX() const;
    float getY() const;
    int getEnergy();
    int getHealth();
    int getShield();
};

#endif