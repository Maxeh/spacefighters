#include <iostream>
#include "GameScreen.hpp"
#include "../Constants.hpp"

GameScreen::GameScreen(std::shared_ptr<GameManager::GameData> gameData) :
    gameData(gameData),
    spaceship((float) WINDOW_WIDTH / 2 - (float) SPACESHIP_WIDTH / 2) {}

void GameScreen::init() {

    closeButton = new SpaceButton(WINDOW_WIDTH - 47, 12, 35, 35);
    soundButton = new SpaceButton(WINDOW_WIDTH - 90, 12, 35, 35);
    soundButtonSprite = new sf::Sprite;

    gameData->assetManager.loadTexture("soundOn", "res/soundOn.png", false);
    gameData->assetManager.loadTexture("soundOff", "res/soundOff.png", true);
    this->gameData->assetManager.loadTexture("background", "res/bg123.png", false);
    this->gameData->assetManager.loadTexture("asteroid", "res/asteroid-60x54.png", false);
    this->gameData->assetManager.loadTexture("spaceship", "res/spaceship-75x74.png", false);
    
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

                    // only start moving window when no button was pressed
                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    mouseButtonPressed = true;
                    for (SpaceButton *button : {closeButton, soundButton}) {
                        if (button->contains(mouseCoordsWindow)) {
                            mouseButtonPressed = false;
                            break; // break for-loop
                        }
                    }
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
                {
                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsInWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    closeButtonHovered = closeButton->contains(mouseCoordsInWindow);
                    soundButtonHovered = soundButton->contains(mouseCoordsInWindow);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseButtonPressed = false;

                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsInWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    if (closeButton->contains(mouseCoordsInWindow)) {
                        this->gameData->assetManager.freeResources();
                        std::exit(0);
                    }
                    if (soundButton->contains(mouseCoordsInWindow)) {
                        if (soundOn) {
                            soundOn = false;
                            this->gameData->assetManager.stopSound(MENU_SOUND);
                        } else {
                            soundOn = true;
                            this->gameData->assetManager.playSound(MENU_SOUND);
                        }
                    }
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
    backgroundShape.setFillColor(COLOR_DARK_BLUE_2);
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

    // border around window
    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10));
    borderShape.setFillColor(sf::Color(255, 255, 255, 0));
    borderShape.setOutlineThickness(5.f);
    borderShape.setOutlineColor(COLOR_DARK_BLUE_1);
    borderShape.setPosition(5.f, 5.f);
    gameData->renderWindow.draw(borderShape);

    // top border
    sf::RectangleShape borderShape2(sf::Vector2f(WINDOW_WIDTH - 10, 0));
    borderShape2.setFillColor(sf::Color(129, 129, 129));
    borderShape2.setOutlineThickness(1.f);
    borderShape2.setOutlineColor(COLOR_LIGHT_BLUE);
    borderShape2.setPosition(5.f, 54.f);
    gameData->renderWindow.draw(borderShape2);

    // title text
    sf::Text titleText;
    titleText.setFont(gameData->assetManager.getFont("menuFont"));
    titleText.setString("spacefighters");
    titleText.setCharacterSize(25);
    titleText.setFillColor(COLOR_LIGHT_BLUE);
    titleText.setPosition(20, 12);
    gameData->renderWindow.draw(titleText);

    // close button
    closeButton->setOutline(closeButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE, 1.f);
    closeButton->setFillColor(new COLOR_DARK_BLUE_1);
    closeButton->setFont(&gameData->assetManager.getFont("menuFont"));
    closeButton->setText(new std::string("x"), 30);
    closeButton->setTextColor(closeButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE);
    closeButton->renderButtonOnWindow(gameData->renderWindow);

    // sound button
    soundButton->setOutline(soundButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE, 1.f);
    soundButton->setFillColor(new COLOR_DARK_BLUE_1);
    std::string soundIcon = soundOn ? "soundOn" : "soundOff";
    sf::Texture& soundTexture = gameData->assetManager.getTexture(soundIcon);
    soundButtonSprite->setTexture(soundTexture);
    soundButton->setSprite(soundButtonSprite);
    soundButton->setSpriteColor(soundButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE);
    soundButton->renderButtonOnWindow(gameData->renderWindow);

    // border
//    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 20));
//    borderShape.setFillColor(sf::Color(255, 255, 255, 0));
//    borderShape.setOutlineThickness(5.f);
//    borderShape.setOutlineColor(sf::Color(165, 23, 23));
//    borderShape.setPosition(5.f, 15.f);
//    this->gameData->renderWindow.draw(borderShape);
    
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