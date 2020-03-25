#ifndef SFML1_MODEL_HPP
#define SFML1_MODEL_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <iostream>
#include "Asteroid.hpp"
#include "Spaceship.hpp"

//enum MoveDirection {Up, Down, Right, Left};

class Model {
    const int ASTEROID_START_POSITION = -400;
    const int ASTEROID_VERTICAL_SPACE = 40;
    const int ASTEROID_HORIZONTAL_SPACE_MIN = 50;
    const int ASTEROID_HORIZONTAL_SPACE_MAX = 250;
    const int NUMBER_OF_ASTEROIDS = 6;
    const double ASTEROID_PROBABILITY = 0.9;
    const int SPACESHIP_WIDTH = 100;
    int windowWidth;
    int windowHeight;
    int asteroidMoveCounter = 0;
    std::vector<Asteroid> asteroids;
    Spaceship spaceship;
public:
    const int ASTEROID_WIDTH = 60;
    const int ASTEROID_HEIGHT = 54;
    enum MoveDirection {Left, Right};

    explicit Model(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight),
            spaceship(windowWidth / 2 - SPACESHIP_WIDTH / 2) {

        addAsteroids();
    }
    void addAsteroids();
    void moveAsteroids();
    void rotateAsteroids();
    void moveSpaceship(MoveDirection moveDirection);
    const std::vector<Asteroid> &getAsteroids() const;
    const Spaceship &getSpaceship() const;
private:
    bool shouldAddAsteroid(double probability) const;
    int randomIntBetween(int iMin, int iMax) const;
    float randomFloatBetween(double fMin, double fMax) const;
};

#endif