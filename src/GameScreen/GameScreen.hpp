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
private:
    static const int NUMBER_OF_MONSTER_ROWS = 2;
    static constexpr float MONSTER_HORIZONTAL_DISTANCE = 34;
    static constexpr float MONSTER_VERTICAL_DISTANCE = 80;
    static const int MONSTER_MISSILE_MAX_TICKS = 10;
    static const int NUMBER_OF_ASTEROID_ROWS = 4;
    static constexpr float ASTEROID_VERTICAL_SPACE = 30;
    static constexpr float ASTEROID_HORIZONTAL_SPACE_MIN = Asteroid::ASTEROID_WIDTH;
    static constexpr float ASTEROID_HORIZONTAL_SPACE_MAX = 300;
    static constexpr float ASTEROID_ROTATION_ANGLE_MIN = -2;
    static constexpr float ASTEROID_ROTATION_ANGLE_MAX = 2;
    static constexpr float ASTEROID_PROBABILITY = 0.4;
    static constexpr float SPACESHIP_MAX_LEFT_POSITION = 5;
    static constexpr float SPACESHIP_MAX_RIGHT_POSITION = WINDOW_WIDTH - Spaceship::SPACESHIP_WIDTH - 5;
    static constexpr float HEALTH_WIDTH = 30;
    static constexpr float HEALTH_HEIGHT = 26;
    static constexpr float HEALTH_HORIZONTAL_DISTANCE = 5;
    static const int LEVEL_COMPLETE_MAX_TICKS = 200;

    bool soundOn = true;
    bool isPause = false;
    int initialWindowX = 0;
    int initialWindowY = 0;
    int mousePositionWhenPressedX = 0;
    int mousePositionWhenPressedY = 0;
    int mousePositionWhenMovedDiffX = 0;
    int mousePositionWhenMovedDiffY = 0;
    bool mouseButtonPressed = false;
    bool monstersMovingRight = true;
    bool monstersMovingLeft = false;
    int monstersMissileTicks = 0;
    int levelCompleteTicks = 0;
    bool levelComplete = false;
    int level = 1;
    int points = 0;
    bool gameOver = false;

    SpaceHeader* spaceHeader = nullptr;
    std::shared_ptr<GameManager::GameData> gameData;
    std::array<std::vector<Asteroid>, 6> asteroidsArray;
    std::vector<Missile> missiles;
    std::vector<Collision> collisions;
    std::array<std::vector<Monster>, 2> monstersArray;
    Spaceship spaceship;

    void initAsteroids();
    void initMonsters();
    void moveSpaceship(float v);
    static float getAsteroidStartY();
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