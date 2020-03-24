#include "Model.hpp"

void Model::addAsteroids() {

    srand(time(0));
    int startY = (windowHeight / 2) - ((NUMBER_OF_ASTEROIDS / 2) * ASTEROID_HEIGHT) -
            ((NUMBER_OF_ASTEROIDS / 2) * VERTICAL_SPACE_BETWEEN_ASTEROIDS) + (VERTICAL_SPACE_BETWEEN_ASTEROIDS / 2);
    for (int i = 0; i < NUMBER_OF_ASTEROIDS; i++) {
        if (((double) rand() / RAND_MAX) < ASTEROID_PROBABILITY) {
            int randNum = rand() % (HORIZONTAL_SPACE_BETWEEN_ASTEROIDS - 0 + 1) + 0;
            asteroids.push_back(Asteroid(ASTEROID_START_POSITION + randNum,
                    startY + i * ASTEROID_HEIGHT + i * VERTICAL_SPACE_BETWEEN_ASTEROIDS));
        }
    }
}

void Model::moveAsteroids() {

    asteroidMoveCounter++;
    for (int i = 0; i < asteroids.size(); i++) {
        asteroids[i].moveX(1);
        if (asteroids[i].getX() > windowWidth) {
            asteroids.erase(asteroids.begin() + i);
            i--;
        }
    }

    int s = asteroidMoveCounter % HORIZONTAL_SPACE_BETWEEN_ASTEROIDS;
    if (s == 0) {
        addAsteroids();
    }
}

std::vector<Asteroid> Model::getAsteroids() const {

    return asteroids;
}