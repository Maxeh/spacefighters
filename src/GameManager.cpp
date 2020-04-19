#include "GameManager.hpp"
#include "GameScreen/GameScreen.hpp"

GameManager::GameManager(int width, int height, const std::string &title) {
    
    this->gameData->renderWindow.create(sf::VideoMode(width, height), title, sf::Style::None);
    this->gameData->renderWindow.setPosition(sf::Vector2i(
        this->gameData->renderWindow.getPosition().x,
        this->gameData->renderWindow.getPosition().y - 20));
    
    this->gameData->screenManager.addScreen(std::make_unique<GameScreen>(this->gameData), false);
    this->run();
}

void GameManager::run() {
    
    sf::Clock clock;
    while (this->gameData->renderWindow.isOpen()) {
        this->gameData->screenManager.processScreenChanges();
        this->gameData->screenManager.getActiveScreen()->handleInput();
    
        if (clock.getElapsedTime().asMilliseconds() >= 100) {
            this->gameData->screenManager.getActiveScreen()->update();
            this->gameData->screenManager.getActiveScreen()->draw();
        }
        
        
    }
}