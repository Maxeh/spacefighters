#ifndef SPACEFIGHTERS_MENUSCREEN_HPP
#define SPACEFIGHTERS_MENUSCREEN_HPP

#include "../Screen.hpp"
#include "../GameManager.hpp"
#include "../Utils/SpaceButton.hpp"
#include "../Utils/SpaceHeader.hpp"

class MenuScreen : public Screen {
private:
    static const std::string MENU_TITLE_STRING;
    static constexpr float MENU_TITLE_BORDER_SIZE = 2.f;
    static const int MENU_TITLE_CHAR_SIZE = 100;
    static constexpr float BUTTON_DEFAULT_BORDER_SIZE = 2.f;
    static const int BUTTON_CHAR_SIZE = 30;

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
    SpaceHeader* spaceHeader = nullptr;
    std::string* singlePlayerString = nullptr;
    std::string* highscoreString = nullptr;
    std::string* aboutString = nullptr;
    sf::Color* colorRed = nullptr;
    sf::Color* colorLightBlue = nullptr;
    sf::Color* colorDarkBlue = nullptr;
    SpaceButton* singlePlayerButton = nullptr;
    SpaceButton* highscoreButton = nullptr;
    SpaceButton* aboutButton = nullptr;
public:
    explicit MenuScreen(std::shared_ptr<GameManager::GameData> gameData);
    ~MenuScreen();
    void init() override;
    void handleInput() override;
    void update() override;
    void draw() override;
};

#endif