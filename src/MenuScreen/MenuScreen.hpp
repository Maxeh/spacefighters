#ifndef SPACEFIGHTERS_MENUSCREEN_HPP
#define SPACEFIGHTERS_MENUSCREEN_HPP

#include "../Screen.hpp"
#include "../GameManager.hpp"
#include "../SpaceButton.hpp"

class MenuScreen : public Screen {
private:
    const int BUTTON_CHAR_SIZE = 30;
    const float BUTTON_DEFAULT_BORDER_SIZE = 2.f;
    const int MENU_TITLE_CHAR_SIZE = 100;
    const float MENU_TITLE_BORDER_SIZE = 5.f;
    const std::string MENU_TITLE_STRING = "MENU";

    std::shared_ptr<GameManager::GameData> gameData;

    std::string* xString;
    std::string* singlePlayerString;
    std::string* twoPlayerString;
    std::string* highscoreString;
    std::string* aboutString;

    sf::Color* colorRed;
    sf::Color* colorLightBlue;
    sf::Color* colorDarkBlue;

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