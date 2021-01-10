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
private:
    const int MAX_FRAME_SKIP = 5;
    const int UPDATE_INTERVAL = 40;

    std::shared_ptr<GameData> gameData = std::make_shared<GameData>();

    void run();
    float getInterpolation(sf::Clock& clock, int nextUpdateInMillis) const;
    static int getClockTimeInMillis(sf::Clock& clock);
};

#endif