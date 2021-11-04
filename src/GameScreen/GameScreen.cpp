#include <iostream>
#include "GameScreen.hpp"

GameScreen::GameScreen(std::shared_ptr<GameManager::GameData> gameData) :
    gameData(std::move(gameData)), spaceship((float) WINDOW_WIDTH / 2 - Spaceship::SPACESHIP_WIDTH / 2, WINDOW_HEIGHT - 120) {}

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
    gameData->assetManager.loadTexture(HEART_TEXTURE, "res/heart.png", false);
    gameData->assetManager.loadFont(GAME_FONT, "res/space_age.ttf");
    gameData->assetManager.loadFont(POINTS_FONT, "res/font.ttf");

    initAsteroids();
    initMonsters();
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
                    if (!levelComplete && !spaceship.isReloading()) {
                        float x = spaceship.getX();
                        float y = spaceship.getY() - Missile::MISSILE_HEIGHT;
                        missiles.emplace_back(x + 4, y, MissileDirection::UP);
                        missiles.emplace_back(x + Spaceship::SPACESHIP_WIDTH - 6, y,
                            MissileDirection::UP);
                        spaceship.reload();
                    }
                }
                break;
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Left) {
                    moveSpaceship(-spaceship.getVelocity());
                    spaceship.resetVelocity();
                    spaceship.setMovingLeft(false);
                }
                if (event.key.code == sf::Keyboard::Right) {
                    moveSpaceship(spaceship.getVelocity());
                    spaceship.resetVelocity();
                    spaceship.setMovingRight(false);
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

    // if the user tabs out of the game, the ongoing movement should be handled correctly
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
        if (spaceship.isMovingLeft()) {
            moveSpaceship(-spaceship.getVelocity());
            spaceship.resetVelocity();
            spaceship.setMovingLeft(false);
        }
        if (spaceship.isMovingRight()) {
            moveSpaceship(spaceship.getVelocity());
            spaceship.resetVelocity();
            spaceship.setMovingRight(false);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !spaceship.isMovingRight()) {
        spaceship.setMovingLeft(true);
        moveSpaceship(-spaceship.getVelocity());
        spaceship.accelerate();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !spaceship.isMovingLeft()) {
        spaceship.setMovingRight(true);
        moveSpaceship(spaceship.getVelocity());
        spaceship.accelerate();
    }
}

void GameScreen::update() {

    // collision detection using shapes
    for (auto& missile : missiles) {
        if (missile.isVisible()) {
            // asteroid collisions
            for (auto& asteroids : asteroidsArray) {
                for (auto& asteroid : asteroids) {
                    if (asteroid.isVisible()) {
                        sf::RectangleShape missileShape(sf::Vector2f(Missile::MISSILE_WIDTH, Missile::MISSILE_HEIGHT));
                        missileShape.setPosition(missile.getX(), missile.getY());

                        // Use factor 0.8 for better collision detection, this is not completely accurate,
                        // but implementing pixel accurate collision detection would be an overkill
                        sf::RectangleShape shape(sf::Vector2f(
                            Asteroid::ASTEROID_WIDTH * 0.8,
                            Asteroid::ASTEROID_HEIGHT * 0.8));
                        shape.setOrigin(
                            static_cast<float>(Asteroid::ASTEROID_WIDTH * 0.8 / 2),
                            static_cast<float>(Asteroid::ASTEROID_HEIGHT * 0.8 / 2));
                        auto posX = asteroid.getX() + Asteroid::ASTEROID_WIDTH * 0.8 / 2;
                        auto posY = asteroid.getY() + Asteroid::ASTEROID_HEIGHT * 0.8 / 2;
                        shape.setPosition(posX, posY);
                        shape.rotate(asteroid.getRotation());

                        if (missileShape.getGlobalBounds().intersects(shape.getGlobalBounds())) {
                            missile.setVisible(false);
                            collisions.emplace_back(missile.getX(), missile.getY(), missile.getMissileDirection());
                        }
                    }
                }
            }

            // monster collisions
            for (auto& monsters : monstersArray) {
                for (auto& monster : monsters) {
                    sf::RectangleShape missileShape(sf::Vector2f(Missile::MISSILE_WIDTH, Missile::MISSILE_HEIGHT));
                    missileShape.setPosition(missile.getX(), missile.getY());

                    // Use factor 0.9 for better collision detection, this is not completely accurate,
                    // but implementing pixel accurate collision detection would be an overkill
                    sf::RectangleShape shape(sf::Vector2f(
                        Monster::MONSTER_WIDTH * 0.9,
                        Monster::MONSTER_HEIGHT * 0.9));
                    shape.setPosition(monster.getX(), monster.getY());

                    if (!monster.isDestroyed() && missileShape.getGlobalBounds().intersects(shape.getGlobalBounds())) {
                        monster.setDestroyed(true);
                        missile.setVisible(false);
                        collisions.emplace_back(missile.getX(), missile.getY(), missile.getMissileDirection());
                        points += 1000;
                    }
                }
            }

            { // spaceship collision
                sf::RectangleShape missileShape(sf::Vector2f(Missile::MISSILE_WIDTH, Missile::MISSILE_HEIGHT));
                missileShape.setPosition(missile.getX(), missile.getY());
                sf::RectangleShape spaceshipShape(sf::Vector2f(Spaceship::SPACESHIP_WIDTH, Spaceship::SPACESHIP_HEIGHT));
                spaceshipShape.setPosition(spaceship.getX(), spaceship.getY());

                if (missileShape.getGlobalBounds().intersects(spaceshipShape.getGlobalBounds())) {
                    missile.setVisible(false);
                    collisions.emplace_back(missile.getX() - spaceship.getX(), missile.getY(),
                        &spaceship, missile.getMissileDirection());

                    if (spaceship.getHealth() == 1) {
                        // game over
                        std::cout << "gameOver" << std::endl;
                        spaceship.setHealth(0);

                    } else {
                        spaceship.setHealth(spaceship.getHealth() - 1);
                    }
                }
            }

            // missile collision
            for (auto& missile2 : missiles) {
                if (&missile == &missile2) {
                    continue;
                }
                if (missile2.isVisible()) {
                    sf::RectangleShape missileShape(sf::Vector2f(Missile::MISSILE_WIDTH, Missile::MISSILE_HEIGHT));
                    missileShape.setPosition(missile.getX(), missile.getY());
                    sf::RectangleShape missile2Shape(sf::Vector2f(Missile::MISSILE_WIDTH, Missile::MISSILE_HEIGHT));
                    missile2Shape.setPosition(missile2.getX(), missile2.getY());

                    if (missileShape.getGlobalBounds().intersects(missile2Shape.getGlobalBounds())) {
                        missile.setVisible(false);
                        missile2.setVisible(false);
                        collisions.emplace_back(missile.getX(), missile.getY(), missile.getMissileDirection());
                    }
                }
            }
        }
    }

    // update missiles
    for (int i = 0; i < missiles.size(); i++) {
        auto& missile = missiles.at(i);
        missile.move();
        if (missile.getMissileDirection() == MissileDirection::UP) {
            if (missile.getY() < -Missile::MISSILE_HEIGHT) {
                missiles.erase(missiles.begin() + i);
                i--;
            }
        } else {
            if (missile.getY() > WINDOW_HEIGHT + Missile::MISSILE_HEIGHT) {
                missiles.erase(missiles.begin() + i);
                i--;
            }
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
            float y = getAsteroidStartY() + static_cast<float>(i) * Asteroid::ASTEROID_HEIGHT +
                static_cast<float>(i) * ASTEROID_VERTICAL_SPACE;
            y = randomFloatBetween(y - ASTEROID_VERTICAL_SPACE / 2, y + ASTEROID_VERTICAL_SPACE / 2);
            float x = asteroids.at(asteroids.size() - 1).getX();
            x -= randomFloatBetween(ASTEROID_HORIZONTAL_SPACE_MIN, ASTEROID_HORIZONTAL_SPACE_MAX);
            float r = randomFloatBetween(ASTEROID_ROTATION_ANGLE_MIN, ASTEROID_ROTATION_ANGLE_MAX);
            asteroids.emplace_back(x, y, r);
            if (randomFloatBetween(0.0, 1.0) > ASTEROID_PROBABILITY)
                asteroids.back().setVisible(false);
        }
    }

    // update collisions
    for (int i = 0; i < collisions.size(); i++) {
        auto& collision = collisions.at(i);
        collision.updateState();
        if (collision.isMaxState()) {
            collisions.erase(collisions.begin() + i);
            i--;
        }
    }

    // find first and last monster of all rows to calculate direction
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
        levelComplete = true;
        if (++levelCompleteTicks == MAX_LEVEL_COMPLETE_TICKS) {
            initMonsters();
            level++;
            levelComplete = false;
            levelCompleteTicks = 0;
        }
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
    std::map<int, Monster*> frontMonstersMap;
    for (int i = 0; i < NUMBER_OF_MONSTER_ROWS; i++) {
        auto& monsters = monstersArray[i];
        for (int e = 0; e < monsters.size(); e++) {
            auto& monster = monsters.at(e);
            if (monster.isDestroyed()) {
                monsters.erase(monsters.begin() + e);
                e--;
            } else {
                monster.updateState(monstersMovingRight);
                frontMonstersMap[monster.getX()] = &monster;
            }
        }
    }
    for (auto& m : frontMonstersMap) {
        // TODO use ticks here
        if (randomFloatBetween(0.0, 1.0) > 0.99) {
            missiles.emplace_back(m.first, m.second->getY() + 50, MissileDirection::DOWN);
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
            sf::RectangleShape borderShape(sf::Vector2f(Missile::MISSILE_WIDTH, Missile::MISSILE_HEIGHT));
            borderShape.setFillColor(missile.getMissileDirection() == MissileDirection::UP ? COLOR_ORANGE : COLOR_GREEN);
            borderShape.setPosition(missile.getX(), missile.getY());
            gameData->renderWindow.draw(borderShape);
        }
    }

    // asteroids
    for (auto& asteroids : asteroidsArray) {
        for (auto& asteroid : asteroids) {
            if (asteroid.isVisible()) {
                sf::Sprite sprite;
                sprite.setOrigin(Asteroid::ASTEROID_WIDTH / 2, Asteroid::ASTEROID_HEIGHT / 2);
                sprite.setTexture(gameData->assetManager.getTexture(ASTEROID_TEXTURE));
                float posX = asteroid.getX() + Asteroid::ASTEROID_WIDTH / 2;
                float posY = asteroid.getY() + Asteroid::ASTEROID_HEIGHT / 2;
                sprite.setPosition(posX, posY);
                sprite.setRotation(asteroid.getRotation());

                // Debugging shape
//                sf::RectangleShape rect;
//                rect.setSize(sf::Vector2f(
//                    (float) (sprite.getLocalBounds().MISSILE_WIDTH * 0.8),
//                    (float) (sprite.getLocalBounds().MISSILE_HEIGHT * 0.8)));
//                rect.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));
//                rect.setOutlineColor(COLOR_ORANGE);
//                rect.setOrigin((float) (ASTEROID_WIDTH * 0.8 / 2), (float) (ASTEROID_HEIGHT * 0.8 / 2));
//                rect.setRotation(asteroid.getRotation());
//                gameData->renderWindow.draw(rect);

                gameData->renderWindow.draw(sprite);
            }
        }
    }

    // collisions
    for (auto& collision : collisions) {
        sf::Sprite sprite;
        sprite.setTexture(gameData->assetManager.getTexture(EXPLOSION_TEXTURE));
        float verticalAdjustment = collision.getMissileDirection() == MissileDirection::UP ? 1.f : -1.f;
        sprite.setPosition(collision.getX(), collision.getY() - 5.f * verticalAdjustment);
        sprite.setTextureRect(sf::IntRect(collision.getSpritePositions()[0],
            collision.getSpritePositions()[1], Collision::COLLISION_WIDTH, Collision::COLLISION_HEIGHT));
        gameData->renderWindow.draw(sprite);
    }

    // monsters
    for (auto& monsters : monstersArray) {
        for (auto& monster: monsters) {
            sf::Sprite sprite;
            sprite.setTexture(gameData->assetManager.getTexture(MONSTER_TEXTURE));
            sprite.setPosition(monster.getX(), monster.getY());
            sprite.setTextureRect(sf::IntRect(monster.getSpritePositions()[0],
                monster.getSpritePositions()[1], Monster::MONSTER_WIDTH, Monster::MONSTER_HEIGHT));
            gameData->renderWindow.draw(sprite);
        }
    }

    // spaceship
    sf::Sprite sprite;
    sprite.setTexture(gameData->assetManager.getTexture(SPACESHIP_TEXTURE));
    if (spaceship.isMovingLeft()) {
        if (spaceship.getX() - spaceship.getVelocity() > SPACESHIP_MAX_LEFT_POSITION) {
            sprite.setPosition(spaceship.getX() - spaceship.getVelocity(), spaceship.getY());
        } else {
            sprite.setPosition(SPACESHIP_MAX_LEFT_POSITION, spaceship.getY());
        }
    } else if (spaceship.isMovingRight()) {
        if (spaceship.getX() + spaceship.getVelocity() < SPACESHIP_MAX_RIGHT_POSITION) {
            sprite.setPosition(spaceship.getX() + spaceship.getVelocity(), spaceship.getY());
        } else {
            sprite.setPosition(SPACESHIP_MAX_RIGHT_POSITION, spaceship.getY());
        }
    } else {
        sprite.setPosition(spaceship.getX(), spaceship.getY());
    }
    gameData->renderWindow.draw(sprite);

    // health
    float healthBoxWidth = static_cast<float>(WINDOW_WIDTH) / 3;
    sf::RectangleShape healthShape(sf::Vector2f(healthBoxWidth, 40));
    healthShape.setOutlineColor(COLOR_DARKER_BLUE);
    healthShape.setFillColor(COLOR_DARK_BLUE);
    healthShape.setPosition(5, WINDOW_HEIGHT - 40);
    gameData->renderWindow.draw(healthShape);
    float healthWidth = HEALTH_WIDTH + HEALTH_HORIZONTAL_DISTANCE;
    float offset = (healthBoxWidth - Spaceship::MAX_HEALTH * healthWidth) / 2 + HEALTH_HORIZONTAL_DISTANCE / 2;
    for (int i = 0; i < Spaceship::MAX_HEALTH; i++) {
        int left = i < spaceship.getHealth() ? 0 : HEALTH_WIDTH;
        sf::Sprite healthSprite;
        healthSprite.setTexture(gameData->assetManager.getTexture(HEART_TEXTURE));
        healthSprite.setPosition(offset + healthWidth * i, WINDOW_HEIGHT - 33);
        healthSprite.setTextureRect(sf::IntRect(left, 0, HEALTH_WIDTH, HEALTH_HEIGHT));
        gameData->renderWindow.draw(healthSprite);
    }

    // points
    sf::RectangleShape shieldShape(sf::Vector2f(static_cast<float>(WINDOW_WIDTH) / 3, 40));
    shieldShape.setOutlineColor(COLOR_CYAN);
    shieldShape.setFillColor(COLOR_CYAN);
    shieldShape.setPosition(5 + static_cast<float>(WINDOW_WIDTH) / 3, WINDOW_HEIGHT - 40);
    gameData->renderWindow.draw(shieldShape);

    // points text
    sf::Text pointsText;
    pointsText.setFont(gameData->assetManager.getFont(POINTS_FONT));
    pointsText.setCharacterSize(20);
    pointsText.setFillColor(COLOR_BLACK);
    std::string stringPoints = std::to_string(points);
    float offsetPointsString = stringPoints.length() * 7.f;
    pointsText.setString(stringPoints);
    pointsText.setPosition(
        5 + static_cast<float>(WINDOW_WIDTH) / 3 + (static_cast<float>(WINDOW_WIDTH) / 3 / 2) - offsetPointsString,
        WINDOW_HEIGHT - 35);
    gameData->renderWindow.draw(pointsText);

    // energy
    sf::RectangleShape energyShape(sf::Vector2f(static_cast<float>(WINDOW_WIDTH) / 3, 40));
    energyShape.setOutlineColor(COLOR_DARKER_BLUE);
    energyShape.setFillColor(COLOR_DARK_BLUE);
    energyShape.setPosition(5 + static_cast<float>(WINDOW_WIDTH) / 3 * 2, WINDOW_HEIGHT - 40);
    gameData->renderWindow.draw(energyShape);

    // level text
    if (levelComplete) {
        sf::Text levelText;
        levelText.setFont(gameData->assetManager.getFont(GAME_FONT));
        levelText.setCharacterSize(50);
        levelText.setFillColor(COLOR_CYAN);
        float offsetLevelString = 150;
        levelText.setString("LEVEL " + std::to_string(level + 1));
        levelText.setPosition(static_cast<float>(WINDOW_WIDTH) / 2 - offsetLevelString, 100);
        gameData->renderWindow.draw(levelText);
    }

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
void GameScreen::initAsteroids() {
    // fill row after row from right to left
    for (int i = 0; i < NUMBER_OF_ASTEROID_ROWS; i++) {
        int asteroidsInRow = static_cast<int>(WINDOW_WIDTH / Asteroid::ASTEROID_WIDTH + 1);
        for (int e = 0; e < asteroidsInRow; e++) {
            float y = getAsteroidStartY();
            y = y + static_cast<float>(i) * Asteroid::ASTEROID_HEIGHT + static_cast<float>(i) * ASTEROID_VERTICAL_SPACE;
            y = randomFloatBetween(y - ASTEROID_VERTICAL_SPACE / 2, y + ASTEROID_VERTICAL_SPACE / 2);
            float x = e > 0 ? asteroidsArray[i].at(e - 1).getX() : WINDOW_WIDTH;
            x -= randomFloatBetween(ASTEROID_HORIZONTAL_SPACE_MIN, ASTEROID_HORIZONTAL_SPACE_MAX);
            float r = randomFloatBetween(ASTEROID_ROTATION_ANGLE_MIN, ASTEROID_ROTATION_ANGLE_MAX);
            asteroidsArray[i].emplace_back(x, y, r);
            if (randomFloatBetween(0.0, 1.0) > ASTEROID_PROBABILITY)
                asteroidsArray[i].back().setVisible(false);
        }
    }
}

void GameScreen::initMonsters() {
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

void GameScreen::moveSpaceship(float v) {

    float x = spaceship.getX() + v;
    if (x < SPACESHIP_MAX_LEFT_POSITION) {
        spaceship.setX(SPACESHIP_MAX_LEFT_POSITION);
        spaceship.setMovingLeft(false);
    } else if (x > SPACESHIP_MAX_RIGHT_POSITION) {
        spaceship.setX(SPACESHIP_MAX_RIGHT_POSITION);
        spaceship.setMovingRight(false);
    } else {
        spaceship.moveX(v);
    }
}

float GameScreen::randomFloatBetween(float fMin, float fMax) {

    float randDouble = (float) rand() / RAND_MAX; // NOLINT(cert-msc50-cpp)
    return fMin + randDouble * (fMax - fMin);
}

float GameScreen::getAsteroidStartY() {

    return ((float) WINDOW_HEIGHT / 2) - (((float) NUMBER_OF_ASTEROID_ROWS / 2) * Asteroid::ASTEROID_HEIGHT) -
        (((float) NUMBER_OF_ASTEROID_ROWS / 2) * ASTEROID_VERTICAL_SPACE) +
        (ASTEROID_VERTICAL_SPACE / 2) + (GAME_HEADER_HEIGHT / 2);
}