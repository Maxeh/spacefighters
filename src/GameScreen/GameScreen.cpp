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
    gameData->assetManager.loadTexture(EXPLOSION_TEXTURE, "res/exp2.png", false);
    gameData->assetManager.loadTexture(MONSTER_TEXTURE, "res/inv3.png", false);
    gameData->assetManager.loadFont(GAME_FONT, "res/space_age.ttf");

    // fill row after row from right to left
    for (int i = 0; i < NUMBER_OF_ASTEROID_ROWS; i++) {
        int asteroidsInRow = static_cast<int>(WINDOW_WIDTH / ASTEROID_WIDTH + 1);
        for (int e = 0; e < asteroidsInRow; e++) {
            float y = getAsteroidStartY();
            y = y + static_cast<float>(i) * ASTEROID_HEIGHT + static_cast<float>(i) * ASTEROID_VERTICAL_SPACE;
            y = randomFloatBetween(y - ASTEROID_VERTICAL_SPACE / 2, y + ASTEROID_VERTICAL_SPACE / 2);
            float x = e > 0 ? asteroidsArray[i].at(e - 1).getX() : WINDOW_WIDTH;
            x -= randomFloatBetween(ASTEROID_HORIZONTAL_SPACE_MIN, ASTEROID_HORIZONTAL_SPACE_MAX);
            float r = randomFloatBetween(ASTEROID_ROTATION_ANGLE[0], ASTEROID_ROTATION_ANGLE[1]);
            asteroidsArray[i].emplace_back(x, y, r);
            if (randomFloatBetween(0.0, 1.0) > 0.8)
                asteroidsArray[i].back().setVisible(false);
        }
    }

    for (int i = 0; i < NUMBER_OF_MONSTER_ROWS; i++) {
        float z = WINDOW_WIDTH - 200;
        int monstersInRow = static_cast<int>(z / (Monster::MONSTER_WIDTH + MONSTER_HORIZONTAL_DISTANCE));
        float monstersWidth = (static_cast<float>(monstersInRow) *
            (Monster::MONSTER_WIDTH + MONSTER_HORIZONTAL_DISTANCE));
        float offset = (WINDOW_WIDTH - monstersWidth) / 2 + MONSTER_HORIZONTAL_DISTANCE / 2;
        for (int e = 0; e < monstersInRow; e++) {
            float y = MONSTER_VERTICAL_DISTANCE * static_cast<float>(i) + MONSTER_VERTICAL_DISTANCE;
            float x = (Monster::MONSTER_WIDTH + MONSTER_HORIZONTAL_DISTANCE) * static_cast<float>(e) + offset;
            monstersArray[i].emplace_back(x, y);
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
                    moveSpaceship(-velocity);
                    velocity = SPACESHIP_DEFAULT_VELOCITY;
                    movingLeft = false;
                }
                if (event.key.code == sf::Keyboard::Right) {
                    moveSpaceship(velocity);
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

    // if the user tabs out of the game, the ongoing movement should be handled correctly
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
        if (movingLeft) {
            moveSpaceship(-velocity);
            velocity = SPACESHIP_DEFAULT_VELOCITY;
            movingLeft = false;
        }
        if (movingRight) {
            moveSpaceship(velocity);
            velocity = SPACESHIP_DEFAULT_VELOCITY;
            movingRight = false;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !movingRight) {
        movingLeft = true;
        moveSpaceship(-velocity);
        if (velocity < SPACESHIP_MAX_VELOCITY) {
            velocity += acceleration;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !movingLeft) {
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

                        // Use factor 0.8 for better collision detection, this is not completely accurate,
                        // but implementing pixel accurate collision detection would be an overkill
                        sf::RectangleShape shape(sf::Vector2f(ASTEROID_WIDTH * 0.8, ASTEROID_HEIGHT * 0.8));
                        shape.setOrigin(
                            static_cast<float>(ASTEROID_WIDTH * 0.8 / 2),
                            static_cast<float>(ASTEROID_HEIGHT * 0.8 / 2));
                        auto posX = asteroid.getX() + ASTEROID_WIDTH * 0.8 / 2;
                        auto posY = asteroid.getY() + ASTEROID_HEIGHT * 0.8 / 2;
                        shape.setPosition(posX, posY);
                        shape.rotate(asteroid.getRotation());

                        if (missileShape.getGlobalBounds().intersects(shape.getGlobalBounds())) {
//                            asteroid.setVisible(false);
                            missile.setVisible(false);
                            collisions.emplace_back(missile.getX(), missile.getY(), 1);
                        }
                    }
                }
            }

            for (auto& monsters : monstersArray) {
                for (auto& monster : monsters) {
                    sf::RectangleShape missileShape(sf::Vector2f(missile.getWidth(), missile.getHeight()));
                    missileShape.setPosition(missile.getX(), missile.getY());

                    sf::RectangleShape shape(sf::Vector2f(
                        Monster::MONSTER_WIDTH * 0.8,
                        Monster::MONSTER_HEIGHT * 0.8));
                    shape.setOrigin(
                        static_cast<float>(Monster::MONSTER_WIDTH * 0.8 / 2),
                        static_cast<float>(Monster::MONSTER_HEIGHT * 0.8 / 2));
                    auto posX = monster.getX() + Monster::MONSTER_WIDTH * 0.8 / 2;
                    auto posY = monster.getY() + Monster::MONSTER_HEIGHT * 0.8 / 2;
                    shape.setPosition(posX, posY);

                    if (missileShape.getGlobalBounds().intersects(shape.getGlobalBounds())) {
                        monster.setDestroyed(true);
                        missile.setVisible(false);
                        collisions.emplace_back(missile.getX(), missile.getY(), 1);
                    }
                }
            }

            // TODO add spaceship collision
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
            float y = getAsteroidStartY() + static_cast<float>(i) * ASTEROID_HEIGHT +
                static_cast<float>(i) * ASTEROID_VERTICAL_SPACE;
            y = randomFloatBetween(y - ASTEROID_VERTICAL_SPACE / 2, y + ASTEROID_VERTICAL_SPACE / 2);
            float x = asteroids.at(asteroids.size() - 1).getX();
            x -= randomFloatBetween(ASTEROID_HORIZONTAL_SPACE_MIN, ASTEROID_HORIZONTAL_SPACE_MAX);
            float r = randomFloatBetween(ASTEROID_ROTATION_ANGLE[0], ASTEROID_ROTATION_ANGLE[1]);
            asteroids.emplace_back(x, y, r);
        }
    }

    // update collisions
    for (int i = 0; i < collisions.size(); i++) {
        auto& collision = collisions.at(i);
        collision.updatePhase();
        if (collision.isMaxPhase()) {
            collisions.erase(collisions.begin() + i);
            i--;
        }
    }

    // Find first and last monster of all rows to calculate direction
    Monster* firstMonsterPtr = nullptr;
    Monster* lastMonsterPtr = nullptr;
    if (!monstersArray[0].empty()) {
        firstMonsterPtr = &monstersArray[0].at(0);
        lastMonsterPtr = &monstersArray[0].at(monstersArray[0].size() - 1);
    }
    for (int i = 1; i < NUMBER_OF_MONSTER_ROWS; i++) {
        if (monstersArray[i].empty()) {
            continue;
        }
        if (firstMonsterPtr == nullptr || firstMonsterPtr->getX() > monstersArray[i].at(0).getX()) {
            firstMonsterPtr = &monstersArray[i].at(0);
        }
        if (lastMonsterPtr == nullptr || lastMonsterPtr->getX() < monstersArray[i].at(monstersArray[i].size() - 1).getX()) {
            lastMonsterPtr = &monstersArray[i].at(monstersArray[i].size() - 1);
        }
    }
    // if one is empty, the other is also empty
    if (lastMonsterPtr == nullptr && firstMonsterPtr == nullptr) {
        std::cout << "WIN" << std::endl;
        return;
    }

    if (monstersMovingRight) {
        if (lastMonsterPtr->getX() > (WINDOW_WIDTH - Monster::MONSTER_WIDTH * 2)) {
            monstersMovingRight = false;
            monstersMovingLeft = true;
        }
    } else if (monstersMovingLeft) {
        if (firstMonsterPtr->getX() < Monster::MONSTER_WIDTH) {
            monstersMovingLeft = false;
            monstersMovingRight = true;
        }
    }

    // update monsters
    for (int i = 0; i < NUMBER_OF_MONSTER_ROWS; i++) {
        auto& monsters = monstersArray[i];
        for (int e = 0; e < monsters.size(); e++) {
            auto& monster = monsters.at(e);
            monster.updateState(monstersMovingLeft);
            if (monster.isDestroyed()) {
                monsters.erase(monsters.begin() + e);
                e--;
            }
        }
    }
}

void GameScreen::draw() {

    gameData->renderWindow.clear(sf::Color::White);

    // background
    sf::RectangleShape backgroundShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundShape.setFillColor(COLOR_DARKER_BLUE);
    gameData->renderWindow.draw(backgroundShape);

    // missiles
    for (auto& missile : missiles) {
        if (missile.isVisible()) {
            sf::RectangleShape borderShape(sf::Vector2f(missile.getWidth(), missile.getHeight()));
            borderShape.setFillColor(COLOR_RED);
            borderShape.setPosition(missile.getX(), missile.getY());
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
                float posX = asteroid.getX() + ASTEROID_WIDTH / 2;
                float posY = asteroid.getY() + ASTEROID_HEIGHT / 2;
                sprite.setPosition(posX, posY);
                sprite.setRotation(asteroid.getRotation());

                // Debugging shape
//                sf::RectangleShape rect;
//                rect.setSize(sf::Vector2f(
//                    (float) (sprite.getLocalBounds().width * 0.8),
//                    (float) (sprite.getLocalBounds().height * 0.8)));
//                rect.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
//                rect.setOutlineColor(COLOR_RED);
//                rect.setOrigin((float) (ASTEROID_WIDTH * 0.8 / 2), (float) (ASTEROID_HEIGHT * 0.8 / 2));
//                rect.setRotation(asteroid.getRotation());
//                gameData->renderWindow.draw(rect);

                gameData->renderWindow.draw(sprite);
            }
        }
    }

    // explosions
    for (auto& collision : collisions) {
        sf::Sprite sprite;
        sprite.setTexture(gameData->assetManager.getTexture(EXPLOSION_TEXTURE));
        sprite.setPosition(collision.getX() - 14,collision.getY() - 14);
        sprite.setTextureRect(sf::IntRect(collision.getCords()[0], collision.getCords()[1],
            30,26));
        gameData->renderWindow.draw(sprite);
    }

    // monsters
    for (auto& monsters : monstersArray) {
        for (auto& monster: monsters) {
            sf::Sprite sprite;
            sprite.setTexture(gameData->assetManager.getTexture(MONSTER_TEXTURE));
            sprite.setPosition(monster.getX(),monster.getY());
            sprite.setTextureRect(sf::IntRect(monster.getSpritePositions()[0],
                monster.getSpritePositions()[1], Monster::MONSTER_WIDTH, Monster::MONSTER_HEIGHT));
            gameData->renderWindow.draw(sprite);
        }
    }

    // spaceship
    sf::Sprite sprite;
    sprite.setTexture(gameData->assetManager.getTexture(SPACESHIP_TEXTURE));
    if (movingLeft) {
        if (spaceship.getX() - velocity > SPACESHIP_MAX_LEFT_POSITION) {
            sprite.setPosition(spaceship.getX() - velocity, spaceship.getY());
        } else {
            sprite.setPosition(SPACESHIP_MAX_LEFT_POSITION, spaceship.getY());
        }
    } else if (movingRight) {
        if (spaceship.getX() + velocity < SPACESHIP_MAX_RIGHT_POSITION) {
            sprite.setPosition(spaceship.getX() + velocity, spaceship.getY());
        } else {
            sprite.setPosition(SPACESHIP_MAX_RIGHT_POSITION, spaceship.getY());
        }
    } else {
        sprite.setPosition(spaceship.getX(), spaceship.getY());
    }
    gameData->renderWindow.draw(sprite);

    // health
    sf::RectangleShape healthShape(sf::Vector2f(static_cast<float>(WINDOW_WIDTH) / 3, 30));
    healthShape.setOutlineColor(COLOR_DARKER_BLUE);
    healthShape.setFillColor(COLOR_RED);
    healthShape.setPosition(5, WINDOW_HEIGHT - 30);
    gameData->renderWindow.draw(healthShape);

//    sf::RectangleShape healthShape2(sf::Vector2f((float) WINDOW_WIDTH / 3, 30));
//    healthShape2.setOutlineColor(COLOR_DARKER_BLUE);
//    healthShape2.setFillColor(COLOR_BLUE);
//    healthShape2.setPosition(5, WINDOW_HEIGHT - 30);
//    gameData->renderWindow.draw(healthShape2);

    // shield
    sf::RectangleShape shieldShape(sf::Vector2f(static_cast<float>(WINDOW_WIDTH) / 3, 30));
    shieldShape.setOutlineColor(COLOR_DARKER_BLUE);
    shieldShape.setFillColor(COLOR_BLUE);
    shieldShape.setPosition(5 + static_cast<float>(WINDOW_WIDTH) / 3, WINDOW_HEIGHT - 30);
    gameData->renderWindow.draw(shieldShape);

    // energy
    sf::RectangleShape energyShape(sf::Vector2f(static_cast<float>(WINDOW_WIDTH) / 3, 30));
    energyShape.setOutlineColor(COLOR_DARKER_BLUE);
    shieldShape.setFillColor(COLOR_DARKER_BLUE);
    energyShape.setPosition(5 + static_cast<float>(WINDOW_WIDTH) / 3 * 2, WINDOW_HEIGHT - 30);
    gameData->renderWindow.draw(energyShape);

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

//int GameScreen::randomIntBetween(float fMin, float fMax) {
//
//    int iMin = (int) fMin;
//    int iMax = (int) fMax;
//    return rand() % (iMax - iMin + 1) + iMin; // NOLINT(cert-msc50-cpp)
//}

float GameScreen::randomFloatBetween(float fMin, float fMax) {

    float randDouble = (float) rand() / RAND_MAX; // NOLINT(cert-msc50-cpp)
    return fMin + randDouble * (fMax - fMin);
}

float GameScreen::getAsteroidStartY() const {

    return ((float) WINDOW_HEIGHT / 2) - (((float) NUMBER_OF_ASTEROID_ROWS / 2) * ASTEROID_HEIGHT) -
        (((float) NUMBER_OF_ASTEROID_ROWS / 2) * ASTEROID_VERTICAL_SPACE) +
        (ASTEROID_VERTICAL_SPACE / 2) + (GAME_HEADER_HEIGHT / 2);
}