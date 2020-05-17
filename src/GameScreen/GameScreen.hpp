#ifndef SPACEFIGHTERS_GAMESCREEN_HPP
#define SPACEFIGHTERS_GAMESCREEN_HPP

#include <memory>
#include "../Screen.hpp"
#include "../GameManager.hpp"
#include "Asteroid.hpp"
#include "Spaceship.hpp"

class GameScreen : public Screen {
private:
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
    double rotation = 0.f;
    bool isPause = false;
    
    int initialWindowX = 0;
    int initialWindowY = 0;
    int mousePositionWhenPressedX = 0;
    int mousePositionWhenPressedY = 0;
    int mousePositionWhenMovedDiffX = 0;
    int mousePositionWhenMovedDiffY = 0;
    bool mouseButtonPressed = false;
    
    float velocity = 2;
    float acceleration = 0.1;
    
    
    std::shared_ptr<GameManager::GameData> gameData;
    std::vector<Asteroid> asteroids;
    Spaceship spaceship;
    void addAsteroids(int startPosition);
    void moveSpaceship(float velocity);
    bool shouldAddAsteroid(double probability) const;
    int randomIntBetween(int iMin, int iMax) const;
    float randomFloatBetween(double fMin, double fMax) const;
public:
    explicit GameScreen(std::shared_ptr<GameManager::GameData> gameData);
    ~GameScreen() = default;
    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;
    void resume() override;
    void pause() override;
};

#endif