#include "SplashScreen.hpp"
#include "../Constants.hpp"
#include "../GameScreen/GameScreen.hpp"
#include "../MenuScreen/MenuScreen.hpp"

SplashScreen::SplashScreen(std::shared_ptr<GameManager::GameData> gameData) : gameData(gameData) {};

void SplashScreen::init() {
    
    this->gameData->assetManager.loadTexture("splashscreen", "res/splashscreen2.png", false);
}

void SplashScreen::handleInput() {
    
    sf::Event event{};
    while (this->gameData->renderWindow.pollEvent(event)) {
        // no input on splash screen
    }
}

void SplashScreen::update() {

    if (clock.getElapsedTime().asMilliseconds() > SPLASH_SCREEN_TIME) {
        this->gameData->screenManager.addScreen(std::make_unique<MenuScreen>(this->gameData), true);
    }
}

void SplashScreen::draw(float interpolation) {
    
    this->gameData->renderWindow.clear(sf::Color::White);
    
    // background
    sf::RectangleShape backgroundShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundShape.setTexture(&this->gameData->assetManager.getTexture("splashscreen"));
    this->gameData->renderWindow.draw(backgroundShape);
    
    // border
    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10));
    borderShape.setFillColor(sf::Color(255, 255, 255, 0));
    borderShape.setOutlineThickness(5.f);
    borderShape.setOutlineColor(COLOR_DARK_BLUE_1);
    borderShape.setPosition(5.f, 5.f);
    this->gameData->renderWindow.draw(borderShape);
    
    this->gameData->renderWindow.display();
}

void SplashScreen::resume() {
    
    // no resume implementation for splash screen
}

void SplashScreen::pause() {
    
    // no pause implementation for splash screen
}