#ifndef SPACEFIGHTERS_GAMEMANAGER_HPP
#define SPACEFIGHTERS_GAMEMANAGER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "ScreenManager.hpp"
#include "AssetManager.hpp"

class GameManager {
public:
    struct GameData {
        ScreenManager screenManager;
        AssetManager assetManager;
        sf::RenderWindow renderWindow;
    };
    GameManager(int width, int height, const std::string& title);
    static const int UPDATES_PER_SECOND = 50;
private:
    static const int UPDATE_INTERVAL = 1000 / UPDATES_PER_SECOND;
    std::shared_ptr<GameData> gameData = std::make_shared<GameData>();
    void runGame();
};

#endif