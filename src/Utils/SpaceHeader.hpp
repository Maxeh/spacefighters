#ifndef SPACEFIGHTERS_SPACEHEADER_HPP
#define SPACEFIGHTERS_SPACEHEADER_HPP

#include <memory>
#include "SpaceButton.hpp"
#include "../GameManager.hpp"

class SpaceHeader {
private:
    const std::string HEADER_TITLE = "spacefighters";
    const sf::Vector2f HEADER_TITLE_POSITION = sf::Vector2f(20, 12);
    const int HEADER_TITLE_SIZE = 25;
    const int HEADER_BUTTON_CHAR_SIZE = 30;
    const float HEADER_BUTTON_BORDER_SIZE = 1.f;
    const float HEADER_BORDER_SIZE = 1.f;

    std::shared_ptr<GameManager::GameData> gameData;
    SpaceButton* soundButton;
    SpaceButton* closeButton;
    sf::Sprite* soundButtonSprite;
    sf::Color* buttonColor;
    sf::Color* buttonOutlineColor;
    sf::Color* buttonHoverOutlineColor;
    std::string* closeString;
    bool soundButtonHovered = false;
    bool closeButtonHovered = false;
public:
    explicit SpaceHeader(std::shared_ptr<GameManager::GameData> gameData);
    ~SpaceHeader();
    void draw();
    void setSoundButtonHovered(bool hovered);
    void setCloseButtonHovered(bool hovered);
    SpaceButton* getSoundButton();
    SpaceButton* getCloseButton();
};

#endif