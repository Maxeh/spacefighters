#include "SplashScreen.hpp"
#include "../Constants.hpp"
#include "../GameScreen/GameScreen.hpp"
#include "../MenuScreen/MenuScreen.hpp"

SplashScreen::SplashScreen(std::shared_ptr<GameManager::GameData> gameData) :
    gameData(gameData) {};

void SplashScreen::init() {

    gameData->assetManager.loadTexture(SPLASHSCREEN_TEXTURE, "res/splashscreen2.png", false);
}

void SplashScreen::handleInput() {

    sf::Event event{};
    while (gameData->renderWindow.pollEvent(event)) {
        // no input on splash screen
    }
}

void SplashScreen::update() {

    if (clock.getElapsedTime().asMilliseconds() > SPLASH_SCREEN_TIME) {
        gameData->screenManager.addScreen(std::make_unique<MenuScreen>(gameData), true);
    }
}

void SplashScreen::draw() {

    gameData->renderWindow.clear(sf::Color::White);

    // background
    sf::RectangleShape backgroundShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundShape.setTexture(&gameData->assetManager.getTexture(SPLASHSCREEN_TEXTURE));
    gameData->renderWindow.draw(backgroundShape);

    // border
    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10));
    borderShape.setFillColor(sf::Color(255, 255, 255, 0));
    borderShape.setOutlineThickness(5.f);
    borderShape.setOutlineColor(COLOR_DARK_BLUE);
    borderShape.setPosition(5.f, 5.f);
    gameData->renderWindow.draw(borderShape);

    gameData->renderWindow.display();
}

void SplashScreen::resume() {

    // no resume implementation for splash screen
}

void SplashScreen::pause() {

    // no pause implementation for splash screen
}