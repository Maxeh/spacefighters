#include <iostream>
#include <SFML/Audio.hpp>
#include "MenuScreen.hpp"
#include "../Constants.hpp"
#include "../GameScreen/GameScreen.hpp"

MenuScreen::MenuScreen(std::shared_ptr<GameManager::GameData> gameData) : gameData(gameData) {

    xString = new std::string("x");
    singlePlayerString = new std::string("player vs. computer");
    twoPlayerString = new std::string("player vs. player");
    highscoreString = new std::string("highscore");
    aboutString = new std::string("about");

    colorRed = new COLOR_RED;
    colorLightBlue = new COLOR_LIGHT_BLUE;
    colorDarkBlue = new COLOR_DARK_BLUE;

    singlePlayerButton = new SpaceButton(50, 300, WINDOW_WIDTH - 100, 50);
    twoPlayerButton = new SpaceButton(50, 370, WINDOW_WIDTH - 100, 50);
    highscoreButton = new SpaceButton(50, 440, WINDOW_WIDTH - 100, 50);
    aboutButton = new SpaceButton(50, 510, WINDOW_WIDTH - 100, 50);
    closeButton = new SpaceButton(WINDOW_WIDTH - 47, 12, 35, 35);
    soundButton = new SpaceButton(WINDOW_WIDTH - 90, 12, 35, 35);
    soundButtonSprite = new sf::Sprite;

    gameData->assetManager.loadTexture(BACKGROUND_TEXTURE, "res/background_menu.png", false);
    gameData->assetManager.loadTexture(SOUND_ON_TEXTURE, "res/soundOn.png", false);
    gameData->assetManager.loadTexture(SOUND_OFF_TEXTURE, "res/soundOff.png", true);
    gameData->assetManager.loadFont(DEFAULT_FONT, "res/space_age.ttf");
    gameData->assetManager.loadSound(GAME_SOUND, "res/spaceSound3.wav");
    gameData->assetManager.playSound(GAME_SOUND);
}

MenuScreen::~MenuScreen() {

    delete singlePlayerButton;
    delete twoPlayerButton;
    delete highscoreButton;
    delete aboutButton;
    delete closeButton;
    delete soundButton;
    delete soundButtonSprite;
}

void MenuScreen::init() {

}

void MenuScreen::handleInput() {
    
    sf::Event event{};
    while (gameData->renderWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                gameData->renderWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    initialWindowX = gameData->renderWindow.getPosition().x;
                    initialWindowY = gameData->renderWindow.getPosition().y;
                    sf::Vector2i mousePositionGlobal = sf::Mouse::getPosition();
                    mousePositionWhenPressedX = mousePositionGlobal.x;
                    mousePositionWhenPressedY = mousePositionGlobal.y;
    
                    // only start moving window when no button was pressed
                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    mouseButtonPressed = true;
                    for (SpaceButton *button : {closeButton, soundButton, singlePlayerButton, twoPlayerButton,
                        highscoreButton, aboutButton}) {
                        if (button->contains(mouseCoordsWindow)) {
                            mouseButtonPressed = false;
                            break; // break for-loop
                        }
                    }
                }
                break;
            case sf::Event::MouseMoved:
                if (mouseButtonPressed) {
                    sf::Vector2i mousePositionGlobal = sf::Mouse::getPosition();
                    mousePositionWhenMovedDiffX = mousePositionWhenPressedX - mousePositionGlobal.x;
                    mousePositionWhenMovedDiffY = mousePositionWhenPressedY - mousePositionGlobal.y;
                    gameData->renderWindow.setPosition(sf::Vector2i(
                        initialWindowX - mousePositionWhenMovedDiffX,
                        initialWindowY - mousePositionWhenMovedDiffY));
                }
                {
                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsInWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    closeButtonHovered = closeButton->contains(mouseCoordsInWindow);
                    soundButtonHovered = soundButton->contains(mouseCoordsInWindow);
                    singlePlayerButtonHovered = singlePlayerButton->contains(mouseCoordsInWindow);
                    twoPlayerButtonHovered = twoPlayerButton->contains(mouseCoordsInWindow);
                    highscoreButtonHovered = highscoreButton->contains(mouseCoordsInWindow);
                    aboutButtonHovered = aboutButton->contains(mouseCoordsInWindow);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseButtonPressed = false;

                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsInWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    if (closeButton->contains(mouseCoordsInWindow)) {
                        this->gameData->assetManager.freeResources();
                        std::exit(0);
                    }
                    if (soundButton->contains(mouseCoordsInWindow)) {
                        if (soundOn) {
                            soundOn = false;
                            this->gameData->assetManager.stopSound(GAME_SOUND);
                        } else {
                            soundOn = true;
                            this->gameData->assetManager.playSound(GAME_SOUND);
                        }
                    }
                    if (singlePlayerButton->contains(mouseCoordsInWindow)) {
                        this->gameData->screenManager.addScreen(std::make_unique<GameScreen>(this->gameData), false);
                        break;
                    }
                    if (twoPlayerButton->contains(mouseCoordsInWindow)) {
                        // start screen
                        break;
                    }
                    if (highscoreButton->contains(mouseCoordsInWindow)) {
                        // start screen
                        break;
                    }
                    if (aboutButton->contains(mouseCoordsInWindow)) {
                        // start screen
                        break;
                    }
                }
                break;
            default:
                break;
        }
    }
}

void MenuScreen::update() {

}

void MenuScreen::draw(float interpolation) {

    gameData->renderWindow.clear(sf::Color::White);
    
    // background
    sf::RectangleShape backgroundShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundShape.setTexture(&this->gameData->assetManager.getTexture(BACKGROUND_TEXTURE));
    backgroundShape.setFillColor(COLOR_BLUE);
    gameData->renderWindow.draw(backgroundShape);

    // border around window
    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10));
    borderShape.setFillColor(COLOR_TRANSPARENT);
    borderShape.setOutlineThickness(GAME_BORDER_SIZE);
    borderShape.setOutlineColor(COLOR_DARK_BLUE);
    borderShape.setPosition(GAME_BORDER_SIZE, GAME_BORDER_SIZE);
    gameData->renderWindow.draw(borderShape);

    // game header box
    sf::RectangleShape headerShape(sf::Vector2f(WINDOW_WIDTH - 10, 50));
    headerShape.setFillColor(sf::Color(COLOR_DARKER_BLUE));
    headerShape.setPosition(GAME_BORDER_SIZE, GAME_BORDER_SIZE);
    gameData->renderWindow.draw(headerShape);

    // border of header
    sf::RectangleShape headerBorder(sf::Vector2f(WINDOW_WIDTH - 10, 0));
    headerBorder.setOutlineThickness(GAME_HEADER_BORDER_SIZE);
    headerBorder.setOutlineColor(COLOR_LIGHT_BLUE);
    headerBorder.setPosition(GAME_BORDER_SIZE, GAME_HEADER_HEIGHT);
    gameData->renderWindow.draw(headerBorder);

    // title text
    sf::Text titleText;
    titleText.setFont(gameData->assetManager.getFont(DEFAULT_FONT));
    titleText.setString(GAME_HEADER_TITLE);
    titleText.setCharacterSize(GAME_HEADER_TITLE_SIZE);
    titleText.setFillColor(COLOR_LIGHT_BLUE);
    titleText.setPosition(GAME_HEADER_TITLE_POSITION);
    gameData->renderWindow.draw(titleText);

    // close button
    closeButton->setOutline(closeButtonHovered ? colorRed : colorLightBlue, GAME_HEADER_BUTTON_BORDER_SIZE);
    closeButton->setFillColor(colorDarkBlue);
    closeButton->setFont(&gameData->assetManager.getFont(DEFAULT_FONT));
    closeButton->setText(xString, GAME_HEADER_BUTTON_CHAR_SIZE);
    closeButton->setTextColor(closeButtonHovered ? colorRed : colorLightBlue);
    closeButton->renderButtonOnWindow(gameData->renderWindow);

    // sound button
    soundButton->setOutline(soundButtonHovered ? colorRed : colorLightBlue, GAME_HEADER_BUTTON_BORDER_SIZE);
    soundButton->setFillColor(colorDarkBlue);
    std::string soundIcon = soundOn ? SOUND_ON_TEXTURE : SOUND_OFF_TEXTURE;
    sf::Texture& soundTexture = gameData->assetManager.getTexture(soundIcon);
    soundButtonSprite->setTexture(soundTexture);
    soundButton->setSprite(soundButtonSprite);
    soundButton->setSpriteColor(soundButtonHovered ? colorRed : colorLightBlue);
    soundButton->renderButtonOnWindow(gameData->renderWindow);

    // menu text
    sf::Text menuText;
    menuText.setFont(gameData->assetManager.getFont(DEFAULT_FONT));
    menuText.setString(MENU_TITLE_STRING);
    menuText.setCharacterSize(MENU_TITLE_CHAR_SIZE);
    menuText.setFillColor(COLOR_LIGHT_BLUE);
    menuText.setPosition((WINDOW_WIDTH - menuText.getLocalBounds().width) / 2,  100);
    menuText.setOutlineColor(COLOR_DARK_BLUE);
    menuText.setOutlineThickness(MENU_TITLE_BORDER_SIZE);
    gameData->renderWindow.draw(menuText);

    // singlePlayerButton
    singlePlayerButton->setOutline(singlePlayerButtonHovered ? colorRed : colorLightBlue, BUTTON_DEFAULT_BORDER_SIZE);
    singlePlayerButton->setFillColor(colorDarkBlue);
    singlePlayerButton->setFont(&gameData->assetManager.getFont(DEFAULT_FONT));
    singlePlayerButton->setText(singlePlayerString, BUTTON_CHAR_SIZE);
    singlePlayerButton->setTextColor(singlePlayerButtonHovered ? colorRed : colorLightBlue);
    singlePlayerButton->renderButtonOnWindow(gameData->renderWindow);

    // twoPlayerButton
    twoPlayerButton->setOutline(twoPlayerButtonHovered ? colorRed : colorLightBlue, BUTTON_DEFAULT_BORDER_SIZE);
    twoPlayerButton->setFillColor(colorDarkBlue);
    twoPlayerButton->setFont(&gameData->assetManager.getFont(DEFAULT_FONT));
    twoPlayerButton->setText(twoPlayerString, BUTTON_CHAR_SIZE);
    twoPlayerButton->setTextColor(twoPlayerButtonHovered ? colorRed : colorLightBlue);
    twoPlayerButton->renderButtonOnWindow(gameData->renderWindow);

    // highscore button
    highscoreButton->setOutline(highscoreButtonHovered ? colorRed : colorLightBlue, BUTTON_DEFAULT_BORDER_SIZE);
    highscoreButton->setFillColor(colorDarkBlue);
    highscoreButton->setFont(&gameData->assetManager.getFont(DEFAULT_FONT));
    highscoreButton->setText(highscoreString, BUTTON_CHAR_SIZE);
    highscoreButton->setTextColor(highscoreButtonHovered ? colorRed : colorLightBlue);
    highscoreButton->renderButtonOnWindow(gameData->renderWindow);

    // about button
    aboutButton->setOutline(aboutButtonHovered ? colorRed : colorLightBlue, BUTTON_DEFAULT_BORDER_SIZE);
    aboutButton->setFillColor(colorDarkBlue);
    aboutButton->setFont(&gameData->assetManager.getFont(DEFAULT_FONT));
    aboutButton->setText(aboutString, BUTTON_CHAR_SIZE);
    aboutButton->setTextColor(aboutButtonHovered ? colorRed : colorLightBlue);
    aboutButton->renderButtonOnWindow(gameData->renderWindow);

    gameData->renderWindow.display();
}

void MenuScreen::resume() {

}

void MenuScreen::pause() {

}