#ifndef SFML1_MODEL_HPP
#define SFML1_MODEL_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <iostream>
#include "Asteroid.hpp"

//enum MoveDirection {Up, Down, Right, Left};

class Model {
    const int ASTEROID_START_POSITION = -400;
    const int VERTICAL_SPACE_BETWEEN_ASTEROIDS = 40;
    const int HORIZONTAL_SPACE_BETWEEN_ASTEROIDS = 300;
    const int NUMBER_OF_ASTEROIDS = 6;
    const double ASTEROID_PROBABILITY = 1;
    int windowWidth;
    int windowHeight;
    int asteroidMoveCounter = 0;
    std::vector<Asteroid> asteroids;
public:
    const int ASTEROID_WIDTH = 60;
    const int ASTEROID_HEIGHT = 54;

    explicit Model(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight) {
        addAsteroids();
    }
    void addAsteroids();
    void moveAsteroids();
    std::vector<Asteroid> getAsteroids() const;
};

#endif