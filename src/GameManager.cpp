#include <iostream>
#include "GameManager.hpp"
#include "GameScreen/GameScreen.hpp"
#include "SplashScreen/SplashScreen.hpp"

GameManager::GameManager(int width, int height, const std::string &title) {
    
    gameData->renderWindow.create(sf::VideoMode(width, height), title, sf::Style::None);
    gameData->renderWindow.setPosition(sf::Vector2i(
        gameData->renderWindow.getPosition().x,
        gameData->renderWindow.getPosition().y - 20));
 
    gameData->screenManager.addScreen(std::make_unique<SplashScreen>(gameData), false);
    run();
}

void GameManager::run() {

    sf::Clock gameClock;
    sf::Clock fpsClock;
    int fpsCounter = 0;
    int nextUpdateInMillis = getClockTimeInMillis(gameClock);
    while (gameData->renderWindow.isOpen()) {

        int loops = 0; // on slow hardware we can skip frames
        while(getClockTimeInMillis(gameClock) >= nextUpdateInMillis && loops < MAX_FRAME_SKIP) {
            gameData->screenManager.processScreenChanges();
            gameData->screenManager.getActiveScreen()->handleInput();
            gameData->screenManager.getActiveScreen()->update();
            nextUpdateInMillis += UPDATE_INTERVAL;
            loops++;
        }

        // rendering is done as often as possible using prediction technique
        float interpolation = getInterpolation(gameClock, nextUpdateInMillis);
        gameData->screenManager.getActiveScreen()->draw(interpolation);

        fpsCounter++;
        if (fpsClock.getElapsedTime().asMilliseconds() >= 1000) {
//            std::cout << "FPS: " << fpsCounter << std::endl;
            fpsCounter = 0;
            fpsClock.restart();
        }
    }
}

float GameManager::getInterpolation(sf::Clock &clock, int nextUpdateInMillis) const {

    return float(getClockTimeInMillis(clock) + UPDATE_INTERVAL - nextUpdateInMillis) / float(UPDATE_INTERVAL);
}

int GameManager::getClockTimeInMillis(sf::Clock& clock) {

    return clock.getElapsedTime().asMilliseconds();
}