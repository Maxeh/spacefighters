#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <iostream>
#include "SpaceButton.hpp"

SpaceButton::SpaceButton(float x, float y, float width, float height) :
    x(x), y(y), width(width), height(height),
    buttonShape(new sf::RectangleShape(sf::Vector2f(width, height))) {}

SpaceButton::~SpaceButton() {

    delete buttonShape;
}

bool SpaceButton::contains(const sf::Vector2f& point) {

    return buttonShape && buttonShape->getGlobalBounds().contains(point);
}

void SpaceButton::setOutline(sf::Color* outlineColor_, float outlineThickness_) {

    outlineColor = outlineColor_;
    outlineThickness = outlineThickness_;
}

void SpaceButton::setFillColor(sf::Color* fillColor_) {

    fillColor = fillColor_;
}

void SpaceButton::setSprite(sf::Sprite* sprite_) {

    sprite = sprite_;
}

void SpaceButton::setSpriteColor(sf::Color* spriteColor_) {

    spriteColor = spriteColor_;
}

void SpaceButton::setFont(sf::Font* textFont_) {

    textFont = textFont_;
}

void SpaceButton::setText(std::string* textString_, int textCharacterSize_) {

    textString = textString_;
    textCharacterSize = textCharacterSize_;
}

void SpaceButton::setTextColor(sf::Color* textColor_) {

    textColor = textColor_;
}

void SpaceButton::renderButtonOnWindow(sf::RenderWindow& renderWindow) {

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

