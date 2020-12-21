#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include "SpaceButton.hpp"

SpaceButton::SpaceButton(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}

SpaceButton::~SpaceButton() {
    
    delete outlineColor;
    delete fillColor;
    delete textString;
    delete textColor;
    delete buttonShape;
    delete sprite;
    delete spriteColor;
}

bool SpaceButton::contains(const sf::Vector2f& point) {
    
    return buttonShape && buttonShape->getGlobalBounds().contains(point);
}

void SpaceButton::setOutline(sf::Color* outlineColor, float outlineThickness) {
    
    this->outlineColor = outlineColor;
    this->outlineThickness = outlineThickness;
}

void SpaceButton::setFillColor(sf::Color* fillColor) {
    
    this->fillColor = fillColor;
}

void SpaceButton::setSprite(sf::Sprite* sprite) {
    
    this->sprite = sprite;
}

void SpaceButton::setSpriteColor(sf::Color* spriteColor) {
    
    this->spriteColor = spriteColor;
}

void SpaceButton::setFont(sf::Font* textFont) {
    
    this->textFont = textFont;
}

void SpaceButton::setText(std::string* textString, int textCharacterSize) {
    
    this->textString = textString;
    this->textCharacterSize = textCharacterSize;
}

void SpaceButton::setTextColor(sf::Color* textColor) {
    
    this->textColor = textColor;
}

void SpaceButton::renderButtonOnWindow(sf::RenderWindow& renderWindow) {
    
    buttonShape = new sf::RectangleShape(sf::Vector2f(width, height));
    buttonShape->setPosition(x, y);

    if (fillColor) {
        buttonShape->setFillColor(*fillColor);
    }

    if (outlineColor) {
        buttonShape->setOutlineThickness(outlineThickness);
        buttonShape->setOutlineColor(*outlineColor);
    }

    renderWindow.draw(*buttonShape);

    if (sprite) {
        sprite->setPosition(x + 4, y + 5);
        sprite->setScale(0.26f, 0.26f);
        if (spriteColor) {
            sprite->setColor(*spriteColor);
        }
        renderWindow.draw(*sprite);
    }

    if (textFont && textString) {
        sf::Text buttonText;
        buttonText.setFont(*textFont);
        buttonText.setString(*textString);
        buttonText.setCharacterSize(textCharacterSize);
        if (textColor) {
            buttonText.setFillColor(*textColor);
        }
        sf::FloatRect textRect = buttonText.getLocalBounds();
        buttonText.setOrigin(
            textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        buttonText.setPosition(
            x + (width / 2),
            y + (height / 2));
        renderWindow.draw(buttonText);
    }
}
