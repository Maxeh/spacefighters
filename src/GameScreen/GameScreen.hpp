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
    const int NUMBER_OF_MONSTERS_ROWS = 2;
    const int NUMBER_OF_MONSTERS_IN_ROW = 8;
    const float MONSTER_WIDTH = 62;
    const float MONSTER_HEIGHT = 45;
    const int NUMBER_OF_ASTEROID_ROWS = 4;
    const float ASTEROID_WIDTH = 60;
    const float ASTEROID_HEIGHT = 54;
    const float ASTEROID_VERTICAL_SPACE = 30;
    const float ASTEROID_HORIZONTAL_SPACE_MIN = ASTEROID_WIDTH;
    const float ASTEROID_HORIZONTAL_SPACE_MAX = 300;
    const float ASTEROID_ROTATION_ANGLE[2] = {-2, 2};
    const float ASTEROID_VELOCITY = 1;
    const float SPACESHIP_WIDTH = 75;
    const float SPACESHIP_MAX_LEFT_POSITION = 5;
    const float SPACESHIP_MAX_RIGHT_POSITION = WINDOW_WIDTH - SPACESHIP_WIDTH - 5;
    const float SPACESHIP_DEFAULT_ACCELERATION = 1;
    const float SPACESHIP_DEFAULT_VELOCITY = 15;
    const float SPACESHIP_MAX_VELOCITY = 40;

    bool isPause = false;
    bool soundOn = true;
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

    SpaceHeader* spaceHeader;
    std::shared_ptr<GameManager::GameData> gameData;
    std::array<std::vector<Asteroid>, 6> asteroidsArray;
    std::vector<Missile> missiles;
    std::vector<Collision> collisions;
    std::vector<Monster> monsters;
    Spaceship spaceship;

    void moveSpaceship(float v);
    static int randomIntBetween(float fMin, float fMax);
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
    float getAsteroidStartY() const;
};

#endif