#ifndef SPACEFIGHTERS_MENUSCREEN_HPP
#define SPACEFIGHTERS_MENUSCREEN_HPP

#include "../Screen.hpp"
#include "../GameManager.hpp"
#include "../SpaceButton.hpp"

class MenuScreen : public Screen {
private:
    std::shared_ptr<GameManager::GameData> gameData;
    SpaceButton* singlePlayerButton;
    SpaceButton* twoPlayerButton;
    SpaceButton* highscoreButton;
    SpaceButton* aboutButton;
    SpaceButton* closeButton;
    SpaceButton* soundButton;
    sf::Sprite* soundButtonSprite;
    bool closeButtonHovered = false;
    bool soundButtonHovered = false;
    bool singlePlayerButtonHovered = false;
    bool twoPlayerButtonHovered = false;
    bool highscoreButtonHovered = false;
    bool aboutButtonHovered = false;
    
    int initialWindowX = 0;
    int initialWindowY = 0;
    int mousePositionWhenPressedX = 0;
    int mousePositionWhenPressedY = 0;
    int mousePositionWhenMovedDiffX = 0;
    int mousePositionWhenMovedDiffY = 0;
    bool mouseButtonPressed = false;
    bool soundOn = true;
public:
    explicit MenuScreen(std::shared_ptr<GameManager::GameData> gameData);
    ~MenuScreen();
    void init() override;
    void handleInput() override;
    void update() override;
    void draw(float interpolation) override;
    void resume() override;
    void pause() override;
};

#endif