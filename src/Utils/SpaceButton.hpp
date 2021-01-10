#ifndef SPACEFIGHTERS_SPACEBUTTON_HPP
#define SPACEFIGHTERS_SPACEBUTTON_HPP

#include <SFML/Graphics.hpp>

class SpaceButton {
    float x;
    float y;
    float width;
    float height;
    float outlineThickness = 1.f;
    int textCharacterSize = 10;

    sf::Color* outlineColor = nullptr;
    sf::Color* fillColor = nullptr;
    sf::Sprite* sprite = nullptr;
    sf::Color* spriteColor = nullptr;
    std::string* textString = nullptr;
    sf::Font* textFont = nullptr;
    sf::Color* textColor = nullptr;
    sf::RectangleShape* buttonShape = nullptr;
public:
    SpaceButton(float x, float y, float width, float height);
    ~SpaceButton();
    bool contains(const sf::Vector2f& point);
    void setOutline(sf::Color* outlineColor_, float outlineThickness_);
    void setFillColor(sf::Color* fillColor_);
    void setSprite(sf::Sprite* sprite_);
    void setSpriteColor(sf::Color* spriteColor_);
    void setFont(sf::Font* textFont_);
    void setText(std::string* textString_, int textCharacterSize_);
    void setTextColor(sf::Color* textColor_);
    void renderButtonOnWindow(sf::RenderWindow& window);
};

#endif