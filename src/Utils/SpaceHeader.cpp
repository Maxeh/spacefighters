#include "SpaceHeader.hpp"
#include "../Constants.hpp"

SpaceHeader::SpaceHeader(std::shared_ptr<GameManager::GameData> gameData) :
    gameData(gameData),
    soundButton(new SpaceButton(WINDOW_WIDTH - 90, 12, 35, 35)),
    closeButton(new SpaceButton(WINDOW_WIDTH - 47, 12, 35, 35)),
    soundButtonSprite(new sf::Sprite),
    buttonColor(new COLOR_DARK_BLUE),
    buttonOutlineColor(new COLOR_CYAN),
    buttonHoverOutlineColor(new COLOR_RED),
    closeString(new std::string("x")) {}

SpaceHeader::~SpaceHeader() {

    delete soundButtonSprite;
    delete buttonColor;
    delete buttonOutlineColor;
    delete buttonHoverOutlineColor;
    delete closeString;

    delete soundButton;
    delete closeButton;
}

void SpaceHeader::draw() {

    // game header box
    sf::RectangleShape headerShape(sf::Vector2f(WINDOW_WIDTH - 10, 50));
    headerShape.setFillColor(sf::Color(COLOR_DARKER_BLUE));
    headerShape.setPosition(WINDOW_BORDER_SIZE, WINDOW_BORDER_SIZE);
    gameData->renderWindow.draw(headerShape);

    // border of header
    sf::RectangleShape headerBorder(sf::Vector2f(WINDOW_WIDTH - 10, 0));
    headerBorder.setOutlineThickness(HEADER_BORDER_SIZE);
    headerBorder.setOutlineColor(COLOR_DARK_BLUE);
    headerBorder.setPosition(WINDOW_BORDER_SIZE, GAME_HEADER_HEIGHT);
    gameData->renderWindow.draw(headerBorder);

    // title text
    sf::Text titleText;
    titleText.setFont(gameData->assetManager.getFont(GAME_FONT));
    titleText.setString(HEADER_TITLE);
    titleText.setCharacterSize(HEADER_TITLE_SIZE);
    titleText.setFillColor(COLOR_CYAN);
    titleText.setPosition(HEADER_TITLE_POSITION);
    gameData->renderWindow.draw(titleText);

    // close button
    closeButton->setOutline(closeButtonHovered ? buttonHoverOutlineColor : buttonOutlineColor,
        HEADER_BUTTON_BORDER_SIZE);
    closeButton->setFillColor(buttonColor);
    closeButton->setFont(&gameData->assetManager.getFont(GAME_FONT));
    closeButton->setText(closeString, HEADER_BUTTON_CHAR_SIZE);
    closeButton->setTextColor(closeButtonHovered ? buttonHoverOutlineColor : buttonOutlineColor);
    closeButton->renderButtonOnWindow(gameData->renderWindow);

    // sound button
    soundButton->setOutline(soundButtonHovered ? buttonHoverOutlineColor : buttonOutlineColor,
        HEADER_BUTTON_BORDER_SIZE);
    soundButton->setFillColor(buttonColor);
    std::string soundIcon = gameData->assetManager.isSoundPlaying(GAME_SOUND) ? SOUND_ON_TEXTURE : SOUND_OFF_TEXTURE;
    sf::Texture& soundTexture = gameData->assetManager.getTexture(soundIcon);
    soundButtonSprite->setTexture(soundTexture);
    soundButton->setSprite(soundButtonSprite);
    soundButton->setSpriteColor(soundButtonHovered ? buttonHoverOutlineColor : buttonOutlineColor);
    soundButton->renderButtonOnWindow(gameData->renderWindow);
}

SpaceButton* SpaceHeader::getSoundButton() {

    return soundButton;
}

SpaceButton* SpaceHeader::getCloseButton() {

    return closeButton;
}

void SpaceHeader::setSoundButtonHovered(bool soundButtonHovered_) {

    soundButtonHovered = soundButtonHovered_;
}

void SpaceHeader::setCloseButtonHovered(bool closeButtonHovered_) {

    closeButtonHovered = closeButtonHovered_;
}
