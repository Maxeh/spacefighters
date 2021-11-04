#ifndef SPACEFIGHTERS_SPACESHIP_HPP
#define SPACEFIGHTERS_SPACESHIP_HPP

#include <SFML/System/Clock.hpp>

class Spaceship {
private:
    static const int RELOAD_TIME = 200;
    static constexpr float DEFAULT_VELOCITY = 15;
    static constexpr float MAX_VELOCITY = 40;
    float x;
    float y;
    int health = MAX_HEALTH;
    int energy = 1000;
    bool movingLeft = false;
    bool movingRight = false;
    sf::Clock reloadTime;
    float velocity = Spaceship::DEFAULT_VELOCITY;
public:
    static constexpr float SPACESHIP_WIDTH = 75;
    static constexpr float SPACESHIP_HEIGHT = 74;
    static const int MAX_HEALTH = 6;

    explicit Spaceship(float x, float y);
    float getX() const;
    void setX(float x);
    void moveX(float x);
    float getY() const;
    int getHealth() const;
    void setHealth(int health);
    int getEnergy() const;
    bool isReloading();
    void reload();
    float getVelocity() const;
    void resetVelocity();
    void accelerate();


    bool isMovingLeft() const;
    void setMovingLeft(bool movingLeft);
    bool isMovingRight() const;
    void setMovingRight(bool movingRight);
};

#endif