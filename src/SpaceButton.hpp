#ifndef SPACEFIGHTERS_SPACEBUTTON_HPP
#define SPACEFIGHTERS_SPACEBUTTON_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class SpaceButton {
private:
    float x;
    float y;
    float width;
    float height;
    float outlineThickness;
    sf::Color* outlineColor;
    sf::Color* fillColor;
    int textCharacterSize;
    std::string* textString;
    sf::Font* textFont;
    sf::Color* textFillColor;
    sf::Texture* texture = nullptr;
    
    sf::RectangleShape* buttonShape;
public:
    
    // TODO refactor this class to prevent NPE, make use of constructor, text & texture is optional, remove setRectangle
    
    SpaceButton() = default;
    ~SpaceButton();
    void setRectangle(float x, float y, float width, float height, float outlineThickness, sf::Color* outlineColor, sf::Color* fillColor);
    void setText(int textCharacterSize, std::string* textString, sf::Font* textFont, sf::Color* textFillColor);
    void setTexture(sf::Texture* texture);
    bool contains(const sf::Vector2f& point);
    void renderButtonOnWindow(sf::RenderWindow& window);
};

#endif