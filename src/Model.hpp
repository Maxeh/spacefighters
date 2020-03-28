#ifndef SFML1_MODEL_HPP
#define SFML1_MODEL_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <iostream>
#include "Asteroid.hpp"
#include "Spaceship.hpp"

class Model {
    const double ASTEROID_PROBABILITY = 1.0;
    const int ASTEROID_WIDTH = 60;
    const int ASTEROID_HEIGHT = 54;
    const int ASTEROID_VERTICAL_SPACE = 40;
    const int ASTEROID_HORIZONTAL_SPACE_MIN = ASTEROID_WIDTH;
    const int ASTEROID_HORIZONTAL_SPACE_MAX = 250;
    // windowWidth - (ASTEROID_HORIZONTAL_SPACE_MAX * 4) - ASTEROID_WIDTH
    const int ASTEROID_START_POSITION = -360;
    const int NUMBER_OF_ASTEROIDS = 6;
    const int SPACESHIP_WIDTH = 100;
    int windowWidth;
    int windowHeight;
    int asteroidMoveCounter = 0;
    std::vector<Asteroid> asteroids;
    Spaceship spaceship;
public:
    explicit Model(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight),
            spaceship(windowWidth / 2 - SPACESHIP_WIDTH / 2) {
        
        addAsteroids(windowWidth - ASTEROID_HORIZONTAL_SPACE_MAX);
        addAsteroids(windowWidth - ASTEROID_HORIZONTAL_SPACE_MAX * 2);
        addAsteroids(windowWidth - ASTEROID_HORIZONTAL_SPACE_MAX * 3);
        addAsteroids(windowWidth - ASTEROID_HORIZONTAL_SPACE_MAX * 4);
    }
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