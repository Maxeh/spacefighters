#ifndef SPACEFIGHTERS_SPACEBUTTON_HPP
#define SPACEFIGHTERS_SPACEBUTTON_HPP

#include <SFML/Graphics.hpp>

class SpaceButton {
private:
    float x;
    float y;
    float width;
    float height;
    float outlineThickness = 1.f;
    sf::Color* outlineColor = nullptr;
    sf::Color* fillColor = nullptr;
    sf::Sprite* sprite = nullptr;
    sf::Color* spriteColor = nullptr;
    int textCharacterSize = 10;
    std::string* textString = nullptr;
    sf::Font* textFont = nullptr;
    sf::Color* textColor = nullptr;
    sf::RectangleShape* buttonShape = nullptr;
public:
    SpaceButton(float x, float y, float width, float height);
    ~SpaceButton();
    bool contains(const sf::Vector2f& point);
    void setOutline(sf::Color* outlineColor, float outlineThickness);
    void setFillColor(sf::Color* fillColor);
    void setSprite(sf::Sprite* sprite);
    void setSpriteColor(sf::Color* spriteColor);
    void setFont(sf::Font* textFont);
    void setText(std::string* textString, int textCharacterSize);
    void setTextColor(sf::Color* textColor);
    void renderButtonOnWindow(sf::RenderWindow& window);
};

#endif