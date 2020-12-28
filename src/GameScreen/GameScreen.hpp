#ifndef SPACEFIGHTERS_GAMESCREEN_HPP
#define SPACEFIGHTERS_GAMESCREEN_HPP

#include <memory>
#include "../Screen.hpp"
#include "../Constants.hpp"
#include "../GameManager.hpp"
#include "../SpaceButton.hpp"
#include "Asteroid.hpp"
#include "Spaceship.hpp"
#include "Missile.hpp"

class GameScreen : public Screen {
private:
    const int ASTEROID_WIDTH = 60;
    const int ASTEROID_HEIGHT = 54;
    const int ASTEROID_VERTICAL_SPACE = 30;
    const int ASTEROID_HORIZONTAL_SPACE_MIN = ASTEROID_WIDTH;
    const int ASTEROID_HORIZONTAL_SPACE_MAX = 300;
    const float ASTEROID_ROTATION_ANGLE[2] = {-5, 5};
    const float ASTEROID_VELOCITY = 8;
    const int NUMBER_OF_ASTEROIDS_IN_COLUMN = 6;
    const int SPACESHIP_WIDTH = 75;
    const float SPACESHIP_MAX_LEFT_POSITION = 5;
    const float SPACESHIP_MAX_RIGHT_POSITION = WINDOW_WIDTH - SPACESHIP_WIDTH - 5;
    const float SPACESHIP_DEFAULT_ACCELERATION = 1;
    const float SPACESHIP_DEFAULT_VELOCITY = 15;
    const float SPACESHIP_MAX_VELOCITY = 40;
    const int HEADER_HEIGHT = 54;
    bool isPause = false;
    bool soundOn = true;

    SpaceButton* closeButton;
    SpaceButton* soundButton;
    sf::Sprite* soundButtonSprite;
    bool closeButtonHovered = false;
    bool soundButtonHovered = false;

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
    float lastInterpolation = 0;

    std::shared_ptr<GameManager::GameData> gameData;
    std::array<std::vector<Asteroid>, 6> asteroidsArray;
    std::vector<Missile> missiles;
    Spaceship spaceship;
    void moveSpaceship(float velocity);
    int randomIntBetween(int iMin, int iMax) const;
    float randomFloatBetween(double fMin, double fMax) const;
public:
    explicit GameScreen(std::shared_ptr<GameManager::GameData> gameData);
    ~GameScreen() = default;
    void init() override;
    void handleInput() override;
    void update() override;
    void draw(float interpolation) override;
    void resume() override;
    void pause() override;

    int getAsteroidStartY();
};

#endif