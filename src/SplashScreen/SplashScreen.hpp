#ifndef SPACEFIGHTERS_SPLASHSCREEN_HPP
#define SPACEFIGHTERS_SPLASHSCREEN_HPP

#include "../Screen.hpp"
#include "../GameManager.hpp"

class SplashScreen : public Screen {
private:
    std::shared_ptr<GameManager::GameData> gameData;
    sf::Clock clock;
public:
    explicit SplashScreen(std::shared_ptr<GameManager::GameData> gameData);
    ~SplashScreen() = default;
    void init() override;
    void handleInput() override;
    void update() override;
    void draw(float interpolation) override;
    void resume() override;
    void pause() override;
};

#endif