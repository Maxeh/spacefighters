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
    int ticks = 0;
    int maxSkipTicks = 5;

    while (gameData->renderWindow.isOpen()) {
        // dont use interpolation predication technique, as this would make the drawing and
        // collision detection much more complicated; we just draw same frames again;
        // we can be quite sure that we can run 50 fps
        while(getClockTimeInMillis(gameClock) >= nextUpdateInMillis && ticks < maxSkipTicks) {
            gameData->screenManager.processScreenChanges();
            gameData->screenManager.getActiveScreen()->handleInput();
            gameData->screenManager.getActiveScreen()->update();
            nextUpdateInMillis += UPDATE_INTERVAL;
            ticks++;
            if (ticks == 5)
                std::cout << "skipping update"<< std::endl;
        }

        ticks = 0;
        gameData->screenManager.getActiveScreen()->draw();
        fpsCounter++;

        if (fpsClock.getElapsedTime().asMilliseconds() > 1000) {
//            std::cout << fpsCounter << std::endl;
            fpsCounter = 0;
            fpsClock.restart();
        }
    }
}

int GameManager::getClockTimeInMillis(sf::Clock& clock) {

    return clock.getElapsedTime().asMilliseconds();
}