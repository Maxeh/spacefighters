#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include "SpaceButton.hpp"
#include "Constants.hpp"

SpaceButton::~SpaceButton() {
    
    delete this->outlineColor;
    delete this->fillColor;
    delete this->textString;
    delete this->textFillColor;
    delete this->buttonShape;
}

void SpaceButton::setRectangle(float x, float y, float width, float height, float outlineThickness,
    sf::Color* outlineColor, sf::Color* fillColor) {
    
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->outlineThickness = outlineThickness;
    this->outlineColor = outlineColor;
    this->fillColor = fillColor;
}

void SpaceButton::setText(int textCharacterSize, std::string* textString, sf::Font* textFont, sf::Color* textFillColor) {
    
    this->textString = textString;
    this->textCharacterSize = textCharacterSize;
    this->textFont = textFont;
    this->textFillColor = textFillColor;
}

void SpaceButton::setTexture(sf::Texture* texture) {
    
    this->texture = texture;
}

bool SpaceButton::contains(const sf::Vector2f& point) {
    
    return this->buttonShape->getGlobalBounds().contains(point);
}

void SpaceButton::renderButtonOnWindow(sf::RenderWindow& renderWindow) {
    
    buttonShape = new sf::RectangleShape(sf::Vector2f(this->width, this->height));
    buttonShape->setFillColor(*this->fillColor);
    buttonShape->setOutlineThickness(this->outlineThickness);
    buttonShape->setOutlineColor(*this->outlineColor);
    buttonShape->setPosition(this->x, this->y);
    if (this->texture) {
        buttonShape->setTexture(this->texture);
    }
    
    sf::Text buttonText;
    buttonText.setFont(*this->textFont);
    buttonText.setString(*this->textString);
    buttonText.setCharacterSize(this->textCharacterSize);
    buttonText.setFillColor(*this->textFillColor);
    sf::FloatRect textRect = buttonText.getLocalBounds();
    buttonText.setOrigin(
        textRect.left + textRect.width/2.0f,
        textRect.top  + textRect.height/2.0f);
    buttonText.setPosition(
        this->x + (this->width / 2),
        this->y + (this->height / 2));
    
    renderWindow.draw(*buttonShape);
    renderWindow.draw(buttonText);
}
