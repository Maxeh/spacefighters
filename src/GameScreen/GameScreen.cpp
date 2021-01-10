#include <iostream>
#include "GameScreen.hpp"

GameScreen::GameScreen(std::shared_ptr<GameManager::GameData> gameData) :
    gameData(gameData), spaceship((float) WINDOW_WIDTH / 2 - SPACESHIP_WIDTH / 2, WINDOW_HEIGHT - 100) {}

GameScreen::~GameScreen() {

    delete spaceHeader;
    for (auto asteroids : asteroidsArray) {
        asteroids.erase(asteroids.begin(), asteroids.end());
    }
    missiles.erase(missiles.begin(), missiles.end());
}

void GameScreen::init() {

    spaceHeader = new SpaceHeader(gameData);

    gameData->assetManager.loadTexture(SOUND_ON_TEXTURE, "res/soundOn.png", false);
    gameData->assetManager.loadTexture(SOUND_OFF_TEXTURE, "res/soundOff.png", true);
    gameData->assetManager.loadTexture(BACKGROUND_TEXTURE, "res/bg123.png", false);
    gameData->assetManager.loadTexture(ASTEROID_TEXTURE, "res/asteroid-60x54.png", false);
    gameData->assetManager.loadTexture(SPACESHIP_TEXTURE, "res/spaceship-75x74.png", false);
    gameData->assetManager.loadFont(GAME_FONT, "res/space_age.ttf");

    for (int i = 0; i < NUMBER_OF_ASTEROID_ROWS; i++) {
        int asteroidsInRow = (int) (WINDOW_WIDTH / ASTEROID_WIDTH + 1);
        for (int e = 0; e < asteroidsInRow; e++) {
            float y = getAsteroidStartY();
            y = y + (float) i * ASTEROID_HEIGHT + (float) i * ASTEROID_VERTICAL_SPACE;
            y = (float) randomIntBetween(y - ASTEROID_VERTICAL_SPACE / 2, y + ASTEROID_VERTICAL_SPACE / 2);
            float x = e > 0 ? asteroidsArray[i].at(e - 1).getX() : WINDOW_WIDTH;
            x -= (float) randomIntBetween(ASTEROID_HORIZONTAL_SPACE_MIN, ASTEROID_HORIZONTAL_SPACE_MAX);
            float r = randomFloatBetween(ASTEROID_ROTATION_ANGLE[0], ASTEROID_ROTATION_ANGLE[1]);
            float v = ASTEROID_VELOCITY;
            asteroidsArray[i].emplace_back(x, y, v, r);
        }
    }
}

bool isPauseKey(const sf::Keyboard::Key& key) {

    return key == sf::Keyboard::P;
}

bool isSpaceKey(const sf::Keyboard::Key& key) {

    return key == sf::Keyboard::Space;
}

void GameScreen::handleInput() {

    sf::Event event{};
    while (gameData->renderWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                gameData->renderWindow.close();
                break;
            case sf::Event::KeyPressed:
                if (isPauseKey(event.key.code)) {
                    isPause = !isPause;
                }
                if (isSpaceKey(event.key.code)) {
                    if (!spaceship.isReloading()) {
                        float x = spaceship.getX();
                        float y = spaceship.getY();
                        missiles.emplace_back(x + 4, y);
                        missiles.emplace_back(x + SPACESHIP_WIDTH - 6, y);
                        spaceship.reload();
                    }
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left) {
                    moveSpaceship(-velocity * lastInterpolation);
                    velocity = SPACESHIP_DEFAULT_VELOCITY;
                    movingLeft = false;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    moveSpaceship(velocity * lastInterpolation);
                    velocity = SPACESHIP_DEFAULT_VELOCITY;
                    movingRight = false;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    initialWindowX = gameData->renderWindow.getPosition().x;
                    initialWindowY = gameData->renderWindow.getPosition().y;
                    sf::Vector2i mousePositionVector = sf::Mouse::getPosition();
                    mousePositionWhenPressedX = mousePositionVector.x;
                    mousePositionWhenPressedY = mousePositionVector.y;

                    // only start moving window when no button was pressed
                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    mouseButtonPressed = true;
                    for (SpaceButton* button : {spaceHeader->getSoundButton(), spaceHeader->getCloseButton()}) {
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
                    gameData->renderWindow.setPosition(sf::Vector2i(
                        initialWindowX - mousePositionWhenMovedDiffX,
                        initialWindowY - mousePositionWhenMovedDiffY));
                }
                {
                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsInWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    spaceHeader->setSoundButtonHovered(spaceHeader->getSoundButton()->contains(mouseCoordsInWindow));
                    spaceHeader->setCloseButtonHovered(spaceHeader->getCloseButton()->contains(mouseCoordsInWindow));
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseButtonPressed = false;

                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsInWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    if (spaceHeader->getSoundButton()->contains(mouseCoordsInWindow)) {
                        if (soundOn) {
                            soundOn = false;
                            gameData->assetManager.stopSound(GAME_SOUND);
                        } else {
                            soundOn = true;
                            gameData->assetManager.playSound(GAME_SOUND);
                        }
                    }
                    if (spaceHeader->getCloseButton()->contains(mouseCoordsInWindow)) {
                        gameData->assetManager.freeResources();
                        std::exit(0);
                    }
                }
                break;
            default:
                break;
        }
    }


    // TODO gameloop + space release timer reset + balken unten + not left/right gleichzeitig
    // TODO UI use constants

    // Checking key is pressed need extra handling

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        movingLeft = true;
        moveSpaceship(-velocity);
        if (velocity < SPACESHIP_MAX_VELOCITY) {
            velocity += acceleration;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        movingRight = true;
        moveSpaceship(velocity);
        if (velocity < SPACESHIP_MAX_VELOCITY) {
            velocity += acceleration;
        }
    }
}

void GameScreen::update() {

    // collision detection using shapes
    for (auto& missile : missiles) {
        if (missile.isVisible()) {
            for (auto& asteroids : asteroidsArray) {
                for (auto& asteroid : asteroids) {
                    if (asteroid.isVisible()) {
                        sf::RectangleShape missileShape(sf::Vector2f(missile.getWidth(), missile.getHeight()));
                        missileShape.setPosition(missile.getX(), missile.getY());

                        sf::Sprite asteroidSprite;
                        asteroidSprite.setOrigin(ASTEROID_WIDTH / 2, ASTEROID_HEIGHT / 2);
                        asteroidSprite.setTexture(gameData->assetManager.getTexture(ASTEROID_TEXTURE));
                        float xPos = asteroid.getX() + ASTEROID_WIDTH / 2;
                        float yPos = asteroid.getY() + ASTEROID_HEIGHT / 2;
                        asteroidSprite.setPosition(xPos, yPos);
                        asteroidSprite.rotate(asteroid.getRotation());
                        // workaround for better real object collision
//                        asteroidSprite.setScale(sf::Vector2f(0.5f, 0.5f));

                        if (missileShape.getGlobalBounds().intersects(asteroidSprite.getGlobalBounds())) {
                            asteroid.setVisible(false);
                            missile.setVisible(false);
                        }
                    }
                }

                // TODO add spaceship collision
            }
        }
    }

    // update missiles
    for (int i = 0; i < missiles.size(); i++) {
        auto& missile = missiles.at(i);
        missile.move();
        if (missile.getY() < -missile.getHeight()) {
            missiles.erase(missiles.begin() + i);
            i--;
        }
    }

    // update asteroids
    for (int i = 0; i < NUMBER_OF_ASTEROID_ROWS; i++) {
        auto& asteroids = asteroidsArray[i];
        for (auto& asteroid : asteroids) {
            asteroid.move();
            asteroid.rotate();
        }
        if (asteroids.at(0).getX() > WINDOW_WIDTH) {
            asteroids.erase(asteroids.begin());
            float y = getAsteroidStartY() + (float) i * ASTEROID_HEIGHT + (float) i * ASTEROID_VERTICAL_SPACE;
            y = (float) randomIntBetween(y - ASTEROID_VERTICAL_SPACE / 2, y + ASTEROID_VERTICAL_SPACE / 2);
            float x = asteroids.at(asteroids.size() - 1).getX();
            x -= (float) randomIntBetween(ASTEROID_HORIZONTAL_SPACE_MIN, ASTEROID_HORIZONTAL_SPACE_MAX);
            float r = randomFloatBetween(ASTEROID_ROTATION_ANGLE[0], ASTEROID_ROTATION_ANGLE[1]);
            float v = ASTEROID_VELOCITY;
            asteroids.emplace_back(x, y, v, r);
        }
    }
}

void GameScreen::draw(float interpolation) {

    lastInterpolation = interpolation;
    gameData->renderWindow.clear(sf::Color::White);

    // background
    sf::RectangleShape backgroundShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundShape.setFillColor(COLOR_DARKER_BLUE);
    gameData->renderWindow.draw(backgroundShape);

    for (auto& missile : missiles) {
        if (missile.isVisible()) {
            sf::RectangleShape borderShape(sf::Vector2f(missile.getWidth(), missile.getHeight()));
            borderShape.setFillColor(COLOR_RED);
            borderShape.setPosition(missile.getX(), missile.getY() - missile.getSpeed() * interpolation);
            gameData->renderWindow.draw(borderShape);
        }
    }

    // asteroids
    for (auto& asteroids : asteroidsArray) {
        for (auto& asteroid : asteroids) {
            if (asteroid.isVisible()) {
                sf::Sprite sprite;
                sprite.setOrigin(ASTEROID_WIDTH / 2, ASTEROID_HEIGHT / 2);
                sprite.setTexture(gameData->assetManager.getTexture(ASTEROID_TEXTURE));
                float posX = asteroid.getX() + ASTEROID_WIDTH / 2 + interpolation * ASTEROID_VELOCITY;
                float posY = asteroid.getY() + ASTEROID_HEIGHT / 2;
                sprite.setPosition(posX, posY);
                sprite.setRotation(asteroid.getRotation() + asteroid.getAngle() * interpolation);
                gameData->renderWindow.draw(sprite);
            }
        }
    }

    // spaceship
    sf::Sprite sprite;
    sprite.setTexture(gameData->assetManager.getTexture(SPACESHIP_TEXTURE));
    if (movingLeft) {
        if (spaceship.getX() - velocity * interpolation > SPACESHIP_MAX_LEFT_POSITION) {
            sprite.setPosition(spaceship.getX() - velocity * interpolation, spaceship.getY());
        } else {
            sprite.setPosition(SPACESHIP_MAX_LEFT_POSITION, spaceship.getY());
        }
    } else if (movingRight) {
        if (spaceship.getX() + velocity * interpolation < SPACESHIP_MAX_RIGHT_POSITION) {
            sprite.setPosition(spaceship.getX() + velocity * interpolation, spaceship.getY());
        } else {
            sprite.setPosition(SPACESHIP_MAX_RIGHT_POSITION, spaceship.getY());
        }
    } else {
        sprite.setPosition(spaceship.getX(), spaceship.getY());
    }
    gameData->renderWindow.draw(sprite);

    // health
//    sf::RectangleShape healthShape(sf::Vector2f(WINDOW_WIDTH - 10, 10));
//    healthShape.setFillColor(COLOR_RED);
//    healthShape.setPosition(5, WINDOW_HEIGHT - 10);
//    gameData->renderWindow.draw(healthShape);

    /** draw not game related UI elements **/

    // border around window
    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10));
    borderShape.setFillColor(COLOR_TRANSPARENT);
    borderShape.setOutlineThickness(WINDOW_BORDER_SIZE);
    borderShape.setOutlineColor(COLOR_DARK_BLUE);
    borderShape.setPosition(WINDOW_BORDER_SIZE, WINDOW_BORDER_SIZE);
    gameData->renderWindow.draw(borderShape);

    spaceHeader->draw();

    gameData->renderWindow.display();
}

void GameScreen::resume() {

}

void GameScreen::pause() {

}

// -------------------------

void GameScreen::moveSpaceship(float v) {

    float x = spaceship.getX() + v;
    if (x < SPACESHIP_MAX_LEFT_POSITION) {
        spaceship.setX(SPACESHIP_MAX_LEFT_POSITION);
        movingLeft = false;
    } else if (x > SPACESHIP_MAX_RIGHT_POSITION) {
        spaceship.setX(SPACESHIP_MAX_RIGHT_POSITION);
        movingRight = false;
    } else {
        spaceship.moveX(v);
    }
}

int GameScreen::randomIntBetween(float fMin, float fMax) {

    int iMin = (int) fMin;
    int iMax = (int) fMax;
    return rand() % (iMax - iMin + 1) + iMin; // NOLINT(cert-msc50-cpp)
}

float GameScreen::randomFloatBetween(float fMin, float fMax) {

    float randDouble = (float) rand() / RAND_MAX; // NOLINT(cert-msc50-cpp)
    return fMin + randDouble * (fMax - fMin);
}

float GameScreen::getAsteroidStartY() const {

    return ((float) WINDOW_HEIGHT / 2) - (((float) NUMBER_OF_ASTEROID_ROWS / 2) * ASTEROID_HEIGHT) -
        (((float) NUMBER_OF_ASTEROID_ROWS / 2) * ASTEROID_VERTICAL_SPACE) +
        (ASTEROID_VERTICAL_SPACE / 2) + (GAME_HEADER_HEIGHT / 2);
}