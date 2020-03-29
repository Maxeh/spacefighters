#include <cstdlib>
#include "Constants.hpp"
#include "Model.hpp"

Model::Model() : spaceship((float) WINDOW_WIDTH / 2 - (float) SPACESHIP_WIDTH / 2) {
    
    int i = 0;
    while ((WINDOW_WIDTH - ASTEROID_HORIZONTAL_SPACE_MAX * i) > -ASTEROID_HORIZONTAL_SPACE_MAX && ++i) {
        addAsteroids(WINDOW_WIDTH - ASTEROID_HORIZONTAL_SPACE_MAX * i);
    }
    asteroidStartPosition = WINDOW_WIDTH - (i * ASTEROID_HORIZONTAL_SPACE_MAX) - ASTEROID_WIDTH;
}

void Model::addAsteroids(int startPosition) {
    
    int startY = (WINDOW_HEIGHT / 2) - ((NUMBER_OF_ASTEROIDS / 2) * ASTEROID_HEIGHT) -
        ((NUMBER_OF_ASTEROIDS / 2) * ASTEROID_VERTICAL_SPACE) + (ASTEROID_VERTICAL_SPACE / 2);
    
    for (int i = 0; i < NUMBER_OF_ASTEROIDS; i++) {
        if (shouldAddAsteroid(ASTEROID_PROBABILITY)) {
            asteroids.emplace_back(
                startPosition + randomIntBetween(ASTEROID_HORIZONTAL_SPACE_MIN, ASTEROID_HORIZONTAL_SPACE_MAX),
                startY + i * ASTEROID_HEIGHT + i * ASTEROID_VERTICAL_SPACE, randomFloatBetween(-1.2, 1.2));
        }
    }
}

void Model::moveAsteroids() {
    
    asteroidMoveCounter++;
    for (int i = 0; i < asteroids.size(); i++) {
        asteroids[i].moveX(1);
        if (asteroids[i].getX() > WINDOW_WIDTH) {
            asteroids.erase(asteroids.begin() + i);
            i--;
        }
    }
    
    int s = asteroidMoveCounter % ASTEROID_HORIZONTAL_SPACE_MAX;
    if (s == 0) {
        asteroidMoveCounter = 0;
        addAsteroids(asteroidStartPosition);
    }
}

void Model::rotateAsteroids() {
    
    for (auto &asteroid : asteroids) {
        asteroid.rotate();
    }
}

void Model::moveSpaceship(float velocity) {
    
    float newX = spaceship.getX() + velocity;
    if (newX < 0) {
        spaceship.setX(1);
    } else if (newX > (float) (WINDOW_WIDTH - SPACESHIP_WIDTH)) {
        spaceship.setX((float) (WINDOW_WIDTH - SPACESHIP_WIDTH));
    } else {
        spaceship.moveX(velocity);
    }
}

const std::vector<Asteroid> &Model::getAsteroids() const {
    
    return asteroids;
}

const Spaceship &Model::getSpaceship() const {
    
    return spaceship;
}

int Model::getAsteroidWidth() const {
    
    return ASTEROID_WIDTH;
}

int Model::getAsteroidHeight() const {
    
    return ASTEROID_HEIGHT;
}

bool Model::shouldAddAsteroid(double probability) const {
    
    return ((double) rand() / RAND_MAX) < probability;
}

int Model::randomIntBetween(int iMin, int iMax) const {
    
    return rand() % (iMax - iMin + 1) + iMin;
}

float Model::randomFloatBetween(double fMin, double fMax) const {
    
    double randDouble = (double) rand() / RAND_MAX;
    return (float) (fMin + randDouble * (fMax - fMin));
}