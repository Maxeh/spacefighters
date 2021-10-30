#ifndef SPACEFIGHTERS_MENUSCREEN_HPP
#define SPACEFIGHTERS_MENUSCREEN_HPP

#include "../Screen.hpp"
#include "../GameManager.hpp"
#include "../Utils/SpaceButton.hpp"
#include "../Utils/SpaceHeader.hpp"

class MenuScreen : public Screen {
    const std::string MENU_TITLE_STRING = "MENU";
    const float MENU_TITLE_BORDER_SIZE = 2.f;
    const int MENU_TITLE_CHAR_SIZE = 100;
    const float BUTTON_DEFAULT_BORDER_SIZE = 2.f;
    const int BUTTON_CHAR_SIZE = 30;

    int initialWindowX = 0;
    int initialWindowY = 0;
    int mousePositionWhenPressedX = 0;
    int mousePositionWhenPressedY = 0;
    int mousePositionWhenMovedDiffX = 0;
    int mousePositionWhenMovedDiffY = 0;
    bool mouseButtonPressed = false;
    bool soundOn = true;
    bool singlePlayerButtonHovered = false;
    bool highscoreButtonHovered = false;
    bool aboutButtonHovered = false;

    std::shared_ptr<GameManager::GameData> gameData;
    SpaceHeader* spaceHeader;
    std::string* singlePlayerString;
    std::string* highscoreString;
    std::string* aboutString;
    sf::Color* colorRed;
    sf::Color* colorLightBlue;
    sf::Color* colorDarkBlue;
    SpaceButton* singlePlayerButton;
    SpaceButton* highscoreButton;
    SpaceButton* aboutButton;
public:
    explicit MenuScreen(std::shared_ptr<GameManager::GameData> gameData);
    ~MenuScreen();
    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;
    void resume() override;
    void pause() override;
};

#endif