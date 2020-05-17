#include <iostream>
#include "GameScreen.hpp"
#include "../Constants.hpp"

GameScreen::GameScreen(std::shared_ptr<GameManager::GameData> gameData) :
    gameData(gameData),
    spaceship((float) WINDOW_WIDTH / 2 - (float) SPACESHIP_WIDTH / 2) {}

void GameScreen::init() {
    
    this->gameData->assetManager.loadTexture("background", "res/bg3.jpg");
    this->gameData->assetManager.loadTexture("asteroid", "res/asteroid-60x54.png");
    this->gameData->assetManager.loadTexture("spaceship", "res/spaceship-75x74.png");
    
    int i = 0;
    while ((WINDOW_WIDTH - ASTEROID_HORIZONTAL_SPACE_MAX * i) > -ASTEROID_HORIZONTAL_SPACE_MAX && ++i) {
        addAsteroids(WINDOW_WIDTH - ASTEROID_HORIZONTAL_SPACE_MAX * i);
    }
    asteroidStartPosition = WINDOW_WIDTH - (i * ASTEROID_HORIZONTAL_SPACE_MAX) - ASTEROID_WIDTH;
}

bool isPauseKey(const sf::Keyboard::Key &key) {
    
    return key == sf::Keyboard::P;
}

void GameScreen::handleInput() {
    
//    sf::Clock clockSpaceship;
    
    sf::Event event{};
    while (this->gameData->renderWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                this->gameData->renderWindow.close();
                break;
            case sf::Event::KeyPressed:
                if (isPauseKey(event.key.code)) {
                    isPause = !isPause;
//                        ShowWindow(mainWin.getSystemHandle(), SW_MINIMIZE);
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left) {
                    velocity = 2;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    velocity = 2;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    initialWindowX = this->gameData->renderWindow.getPosition().x;
                    initialWindowY = this->gameData->renderWindow.getPosition().y;
                    sf::Vector2i mousePositionVector = sf::Mouse::getPosition();
                    mousePositionWhenPressedX = mousePositionVector.x;
                    mousePositionWhenPressedY = mousePositionVector.y;
                    mouseButtonPressed = true;
                }
                break;
            case sf::Event::MouseMoved:
                if (mouseButtonPressed) {
                    sf::Vector2i v = sf::Mouse::getPosition();
                    mousePositionWhenMovedDiffX = mousePositionWhenPressedX - v.x;
                    mousePositionWhenMovedDiffY = mousePositionWhenPressedY - v.y;
                    this->gameData->renderWindow.setPosition(sf::Vector2i(
                        initialWindowX - mousePositionWhenMovedDiffX,
                        initialWindowY - mousePositionWhenMovedDiffY));
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseButtonPressed = false;
                }
                break;
            default:
                break;
        }
    }
    
    bool shouldMoveSpaceship = true;
//    if (clockSpaceship.getElapsedTime().asMilliseconds() >= 5) {
//        shouldMoveSpaceship = true;
//        clockSpaceship.restart();
//    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        if (shouldMoveSpaceship) {
            moveSpaceship(-velocity);
            if (velocity < 5) {
                velocity += acceleration;
            }
        }
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        if (shouldMoveSpaceship) {
            moveSpaceship(velocity);
            if (velocity < 5) {
                velocity += acceleration;
            }
        }
    }
}

void GameScreen::update() {
    
    // move asteroids
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
    
    // rotate asteroids
    for (auto &asteroid : asteroids) {
        asteroid.rotate();
    }
}

void GameScreen::draw() {
    
    this->gameData->renderWindow.clear(sf::Color::White);
    
    // background
    sf::RectangleShape backgroundShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundShape.setTexture(&this->gameData->assetManager.getTexture("background"));
    this->gameData->renderWindow.draw(backgroundShape);
    
    // asteroids
    for (const Asteroid &asteroid : this->asteroids) {
        sf::Sprite sprite;
        sprite.setOrigin((float) ASTEROID_WIDTH / 2, (float) ASTEROID_HEIGHT / 2);
        sprite.setTexture(this->gameData->assetManager.getTexture("asteroid"));
        sprite.setPosition(
            (float) asteroid.getX() + (float) ASTEROID_WIDTH / 2,
            (float) asteroid.getY() + (float) ASTEROID_HEIGHT / 2);
        sprite.rotate(asteroid.getRotation());
        this->gameData->renderWindow.draw(sprite);
    }
    
    // spaceship
    sf::Sprite sprite;
    sprite.setTexture(this->gameData->assetManager.getTexture("spaceship"));
    sprite.setPosition(this->spaceship.getX(), (float) WINDOW_HEIGHT - 100);
    this->gameData->renderWindow.draw(sprite);
    
    // border
    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 20));
    borderShape.setFillColor(sf::Color(255, 255, 255, 0));
    borderShape.setOutlineThickness(5.f);
    borderShape.setOutlineColor(sf::Color(165, 23, 23));
    borderShape.setPosition(5.f, 15.f);
    this->gameData->renderWindow.draw(borderShape);
    
    this->gameData->renderWindow.display();
    
    rotation = rotation + 2.0;
}

void GameScreen::resume() {

}

void GameScreen::pause() {

}

// -------------------------

void GameScreen::addAsteroids(int startPosition) {
    
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

void GameScreen::moveSpaceship(float velocity) {
    
    float newX = spaceship.getX() + velocity;
    if (newX < 0) {
        spaceship.setX(1);
    } else if (newX > (float) (WINDOW_WIDTH - SPACESHIP_WIDTH)) {
        spaceship.setX((float) (WINDOW_WIDTH - SPACESHIP_WIDTH));
    } else {
        spaceship.moveX(velocity);
    }
}

bool GameScreen::shouldAddAsteroid(double probability) const {
    
    return ((double) rand() / RAND_MAX) < probability;
}

int GameScreen::randomIntBetween(int iMin, int iMax) const {
    
    return rand() % (iMax - iMin + 1) + iMin;
}

float GameScreen::randomFloatBetween(double fMin, double fMax) const {
    
    double randDouble = (double) rand() / RAND_MAX;
    return (float) (fMin + randDouble * (fMax - fMin));
}