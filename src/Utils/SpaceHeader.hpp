#ifndef SPACEFIGHTERS_SPACEHEADER_HPP
#define SPACEFIGHTERS_SPACEHEADER_HPP

#include <memory>
#include "SpaceButton.hpp"
#include "../GameManager.hpp"

class SpaceHeader {
    static const std::string HEADER_TITLE;
    static const sf::Vector2f HEADER_TITLE_POSITION;
    static const int HEADER_TITLE_SIZE = 25;
    static const int HEADER_BUTTON_CHAR_SIZE = 30;
    static constexpr float HEADER_BUTTON_BORDER_SIZE = 1.f;
    static constexpr float HEADER_BORDER_SIZE = 1.f;

    bool soundButtonHovered = false;
    bool closeButtonHovered = false;

    std::shared_ptr<GameManager::GameData> gameData;
    SpaceButton* soundButton;
    SpaceButton* closeButton;
    sf::Sprite* soundButtonSprite;
    sf::Color* buttonColor;
    sf::Color* buttonOutlineColor;
    sf::Color* buttonHoverOutlineColor;
    std::string* closeString;
public:
    explicit SpaceHeader(std::shared_ptr<GameManager::GameData> gameData);
    ~SpaceHeader();
    void draw();
    void setSoundButtonHovered(bool soundButtonHovered_);
    void setCloseButtonHovered(bool closeButtonHovered_);
    SpaceButton* getSoundButton();
    SpaceButton* getCloseButton();
};

#endif