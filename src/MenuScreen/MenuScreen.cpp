#include <iostream>
#include <SFML/Audio.hpp>
#include "MenuScreen.hpp"
#include "../Constants.hpp"
#include "../GameScreen/GameScreen.hpp"

MenuScreen::MenuScreen(std::shared_ptr<GameManager::GameData> gameData) :
    gameData(gameData) {

    singlePlayerString = new std::string("player vs. computer");
    highscoreString = new std::string("highscore");
    aboutString = new std::string("about");

    colorRed = new COLOR_RED;
    colorLightBlue = new COLOR_BLACK;
    colorDarkBlue = new COLOR_BLUE;

    spaceHeader = new SpaceHeader(gameData);
    singlePlayerButton = new SpaceButton(50, 300, WINDOW_WIDTH - 100, 50);
    highscoreButton = new SpaceButton(50, 370, WINDOW_WIDTH - 100, 50);
    aboutButton = new SpaceButton(50, 440, WINDOW_WIDTH - 100, 50);

    gameData->assetManager.loadTexture(BACKGROUND_TEXTURE, "res/background_menu.png", false);
    gameData->assetManager.loadTexture(SOUND_ON_TEXTURE, "res/soundOn.png", false);
    gameData->assetManager.loadTexture(SOUND_OFF_TEXTURE, "res/soundOff.png", true);
    gameData->assetManager.loadFont(GAME_FONT, "res/space_age.ttf");
    gameData->assetManager.loadSound(GAME_SOUND, "res/space.wav");
    gameData->assetManager.playSound(GAME_SOUND);
}

MenuScreen::~MenuScreen() {

    delete singlePlayerString;
    delete highscoreString;
    delete aboutString;

    delete colorRed;
    delete colorLightBlue;
    delete colorDarkBlue;

    delete spaceHeader;
    delete singlePlayerButton;
    delete highscoreButton;
    delete aboutButton;
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
                    for (SpaceButton* button : {spaceHeader->getSoundButton(), spaceHeader->getCloseButton(),
                        singlePlayerButton, highscoreButton, aboutButton}) {
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

                    spaceHeader->setSoundButtonHovered(spaceHeader->getSoundButton()->contains(mouseCoordsInWindow));
                    spaceHeader->setCloseButtonHovered(spaceHeader->getCloseButton()->contains(mouseCoordsInWindow));
                    singlePlayerButtonHovered = singlePlayerButton->contains(mouseCoordsInWindow);
                    highscoreButtonHovered = highscoreButton->contains(mouseCoordsInWindow);
                    aboutButtonHovered = aboutButton->contains(mouseCoordsInWindow);
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseButtonPressed = false;

                    sf::Vector2i mousePositionInWindow = sf::Mouse::getPosition(gameData->renderWindow);
                    sf::Vector2f mouseCoordsInWindow = gameData->renderWindow.mapPixelToCoords(mousePositionInWindow);
                    if (spaceHeader->getSoundButton()->contains(mouseCoordsInWindow)) {
                        if (soundOn) {
                            soundOn = false;
                            gameData->assetManager.stopSound(GAME_SOUND);
                        } else {
                            soundOn = true;
                            gameData->assetManager.playSound(GAME_SOUND);
                        }
                    }
                    if (spaceHeader->getCloseButton()->contains(mouseCoordsInWindow)) {
                        gameData->assetManager.freeResources();
                        std::exit(0);
                    }
                    if (singlePlayerButton->contains(mouseCoordsInWindow)) {
                        gameData->screenManager.addScreen(std::make_unique<GameScreen>(gameData), false);
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

    // no update on menu screen
}

void MenuScreen::draw() {

    gameData->renderWindow.clear(sf::Color::White);

    // background
    sf::RectangleShape backgroundShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundShape.setTexture(&gameData->assetManager.getTexture(BACKGROUND_TEXTURE));
//    backgroundShape.setFillColor(COLOR_BLUE);
    gameData->renderWindow.draw(backgroundShape);

    // border around window
    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10));
    borderShape.setFillColor(COLOR_TRANSPARENT);
    borderShape.setOutlineThickness(WINDOW_BORDER_SIZE);
    borderShape.setOutlineColor(COLOR_DARK_BLUE);
    borderShape.setPosition(WINDOW_BORDER_SIZE, WINDOW_BORDER_SIZE);
    gameData->renderWindow.draw(borderShape);

    // header
    spaceHeader->draw();

    // menu text
    sf::Text menuText;
    menuText.setFont(gameData->assetManager.getFont(GAME_FONT));
    menuText.setString(MENU_TITLE_STRING);
    menuText.setCharacterSize(MENU_TITLE_CHAR_SIZE);
    menuText.setFillColor(COLOR_BLACK);
    menuText.setPosition((WINDOW_WIDTH - menuText.getLocalBounds().width) / 2, 100);
    menuText.setOutlineColor(COLOR_BLUE);
    menuText.setOutlineThickness(MENU_TITLE_BORDER_SIZE);
    gameData->renderWindow.draw(menuText);

    // singlePlayerButton
    singlePlayerButton->setOutline(singlePlayerButtonHovered ? colorRed : colorLightBlue, BUTTON_DEFAULT_BORDER_SIZE);
    singlePlayerButton->setFillColor(colorDarkBlue);
    singlePlayerButton->setFont(&gameData->assetManager.getFont(GAME_FONT));
    singlePlayerButton->setText(singlePlayerString, BUTTON_CHAR_SIZE);
    singlePlayerButton->setTextColor(singlePlayerButtonHovered ? colorRed : colorLightBlue);
    singlePlayerButton->renderButtonOnWindow(gameData->renderWindow);

    // highscore button
    highscoreButton->setOutline(highscoreButtonHovered ? colorRed : colorLightBlue, BUTTON_DEFAULT_BORDER_SIZE);
    highscoreButton->setFillColor(colorDarkBlue);
    highscoreButton->setFont(&gameData->assetManager.getFont(GAME_FONT));
    highscoreButton->setText(highscoreString, BUTTON_CHAR_SIZE);
    highscoreButton->setTextColor(highscoreButtonHovered ? colorRed : colorLightBlue);
    highscoreButton->renderButtonOnWindow(gameData->renderWindow);

    // about button
    aboutButton->setOutline(aboutButtonHovered ? colorRed : colorLightBlue, BUTTON_DEFAULT_BORDER_SIZE);
    aboutButton->setFillColor(colorDarkBlue);
    aboutButton->setFont(&gameData->assetManager.getFont(GAME_FONT));
    aboutButton->setText(aboutString, BUTTON_CHAR_SIZE);
    aboutButton->setTextColor(aboutButtonHovered ? colorRed : colorLightBlue);
    aboutButton->renderButtonOnWindow(gameData->renderWindow);

    gameData->renderWindow.display();
}

void MenuScreen::resume() {

    // no resume on menu screen
}

void MenuScreen::pause() {

    // no pause on menu screen
}