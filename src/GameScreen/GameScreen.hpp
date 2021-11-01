#ifndef SPACEFIGHTERS_GAMESCREEN_HPP
#define SPACEFIGHTERS_GAMESCREEN_HPP

#include <memory>
#include "../Screen.hpp"
#include "../Constants.hpp"
#include "../GameManager.hpp"
#include "../Utils/SpaceButton.hpp"
#include "Asteroid.hpp"
#include "Spaceship.hpp"
#include "Missile.hpp"
#include "../Utils/SpaceHeader.hpp"
#include "Collision.hpp"
#include "Monster.hpp"

class GameScreen : public Screen {
    int NUMBER_OF_MONSTER_ROWS = 2;
    float MONSTER_HORIZONTAL_DISTANCE = 34;
    float MONSTER_VERTICAL_DISTANCE = 80;
    int NUMBER_OF_ASTEROID_ROWS = 4;
    float ASTEROID_WIDTH = 60;
    float ASTEROID_HEIGHT = 54;
    float ASTEROID_VERTICAL_SPACE = 30;
    float ASTEROID_HORIZONTAL_SPACE_MIN = ASTEROID_WIDTH;
    float ASTEROID_HORIZONTAL_SPACE_MAX = 300;
    float ASTEROID_ROTATION_ANGLE[2] = {-2, 2};
    float ASTEROID_PROBABILITY = 0.5;
    float SPACESHIP_WIDTH = 75;
    float SPACESHIP_MAX_LEFT_POSITION = 5;
    float SPACESHIP_MAX_RIGHT_POSITION = WINDOW_WIDTH - SPACESHIP_WIDTH - 5;
    float SPACESHIP_DEFAULT_ACCELERATION = 1;
    float SPACESHIP_DEFAULT_VELOCITY = 15;
    float SPACESHIP_MAX_VELOCITY = 40;
    int MAX_LEVEL_COMPLETE_TICKS = 200;

    bool soundOn = true;
    bool isPause = false;
    int initialWindowX = 0;
    int initialWindowY = 0;
    int mousePositionWhenPressedX = 0;
    int mousePositionWhenPressedY = 0;
    int mousePositionWhenMovedDiffX = 0;
    int mousePositionWhenMovedDiffY = 0;
    bool mouseButtonPressed = false;
    float velocity = SPACESHIP_DEFAULT_VELOCITY;
    float acceleration = SPACESHIP_DEFAULT_ACCELERATION;
    bool movingLeft = false;
    bool movingRight = false;
    bool monstersMovingRight = true;
    bool monstersMovingLeft = false;
    int levelCompleteTicks = 0;
    bool levelComplete = false;
    int level = 1;
    int points = 0;

    SpaceHeader* spaceHeader;
    std::shared_ptr<GameManager::GameData> gameData;
    std::array<std::vector<Asteroid>, 6> asteroidsArray;
    std::vector<Missile> missiles;
    std::vector<Collision> collisions;
    std::array<std::vector<Monster>, 2> monstersArray;
    Spaceship spaceship;

    void initAsteroids();
    void initMonsters();
    void moveSpaceship(float v);
    float getAsteroidStartY() const;
    static float randomFloatBetween(float fMin, float fMax);
public:
    explicit GameScreen(std::shared_ptr<GameManager::GameData> gameData);
    ~GameScreen();
    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;
    void resume() override;
    void pause() override;
};

#endif