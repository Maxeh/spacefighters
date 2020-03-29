#ifndef SPACEFIGHTERS_MODEL_HPP
#define SPACEFIGHTERS_MODEL_HPP

#include <vector>
#include "Asteroid.hpp"
#include "Spaceship.hpp"

class Model {
    const double ASTEROID_PROBABILITY = 1.0;
    const int ASTEROID_WIDTH = 60;
    const int ASTEROID_HEIGHT = 54;
    const int ASTEROID_VERTICAL_SPACE = 40;
    const int ASTEROID_HORIZONTAL_SPACE_MIN = ASTEROID_WIDTH;
    const int ASTEROID_HORIZONTAL_SPACE_MAX = 250;
    const int NUMBER_OF_ASTEROIDS = 6;
    const int SPACESHIP_WIDTH = 100;
    int asteroidStartPosition = 0;
    int asteroidMoveCounter = 0;
    std::vector<Asteroid> asteroids;
    Spaceship spaceship;
public:
    Model();
    void addAsteroids(int startPosition);
    void moveAsteroids();
    void rotateAsteroids();
    void moveSpaceship(float velocity);
    const std::vector<Asteroid> &getAsteroids() const;
    const Spaceship &getSpaceship() const;
    int getAsteroidWidth() const;
    int getAsteroidHeight() const;
private:
    bool shouldAddAsteroid(double probability) const;
    int randomIntBetween(int iMin, int iMax) const;
    float randomFloatBetween(double fMin, double fMax) const;
};

#endif