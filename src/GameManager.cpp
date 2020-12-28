#include <iostream>
#include "GameManager.hpp"
#include "GameScreen/GameScreen.hpp"
#include "SplashScreen/SplashScreen.hpp"

GameManager::GameManager(int width, int height, const std::string &title) {
    
    this->gameData->renderWindow.create(sf::VideoMode(width, height), title, sf::Style::None);
    this->gameData->renderWindow.setPosition(sf::Vector2i(
        this->gameData->renderWindow.getPosition().x,
        this->gameData->renderWindow.getPosition().y - 20));
 
    this->gameData->screenManager.addScreen(std::make_unique<SplashScreen>(this->gameData), false);
    this->run();
}

void GameManager::run() {

    sf::Clock gameClock;
    sf::Clock fpsClock;
    int fpsCounter = 0;
    int nextUpdateInMillis = getClockTimeInMillis(gameClock);
    while (this->gameData->renderWindow.isOpen()) {

        int loops = 0; // on slow hardware we can skip frames
        while(getClockTimeInMillis(gameClock) >= nextUpdateInMillis && loops < MAX_FRAME_SKIP) {
            this->gameData->screenManager.processScreenChanges();
            this->gameData->screenManager.getActiveScreen()->handleInput();
            this->gameData->screenManager.getActiveScreen()->update();
            nextUpdateInMillis += UPDATE_INTERVAL;
            loops++;
        }

        // rendering is done as often as possible using prediction technique
        float interpolation = getInterpolation(gameClock, nextUpdateInMillis);
        this->gameData->screenManager.getActiveScreen()->draw(interpolation);

        fpsCounter++;
        if (fpsClock.getElapsedTime().asMilliseconds() >= 1000) {
//            std::cout << "FPS: " << fpsCounter << std::endl;
            fpsCounter = 0;
            fpsClock.restart();
        }
    }
}

int GameManager::getClockTimeInMillis(sf::Clock& clock) {

    return clock.getElapsedTime().asMilliseconds();
}

float GameManager::getInterpolation(sf::Clock &clock, int nextUpdateInMillis) {

    return float(getClockTimeInMillis(clock) + UPDATE_INTERVAL - nextUpdateInMillis) / float(UPDATE_INTERVAL);
}