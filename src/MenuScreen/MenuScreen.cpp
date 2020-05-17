#include <iostream>
#include "MenuScreen.hpp"
#include "../Constants.hpp"
#include "../SpaceButton.hpp"

MenuScreen::MenuScreen(std::shared_ptr<GameManager::GameData> gameData) : gameData(gameData) {}

void MenuScreen::init() {
    
    this->gameData->assetManager.loadTexture("background", "res/bg3.jpg");
    this->gameData->assetManager.loadTexture("soundOn", "res/sound3.png");
    this->gameData->assetManager.loadTexture("soundOff", "res/sound4.png");
    this->gameData->assetManager.loadFont("menuFont", "res/space_age.ttf");
}

void MenuScreen::handleInput() {
    
    sf::Event event{};
    while (this->gameData->renderWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                this->gameData->renderWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    initialWindowX = this->gameData->renderWindow.getPosition().x;
                    initialWindowY = this->gameData->renderWindow.getPosition().y;
                    sf::Vector2i mousePositionVector = sf::Mouse::getPosition();
                    mousePositionWhenPressedX = mousePositionVector.x;
                    mousePositionWhenPressedY = mousePositionVector.y;
                    mouseButtonPressed = true;
                }
                {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(this->gameData->renderWindow);
                    sf::Vector2f mouseCoords = this->gameData->renderWindow.mapPixelToCoords(mousePosition);
                    if (buttonClose.contains(mouseCoords)) {
                        std::exit(0);
                    }
                }
                break;
            case sf::Event::MouseMoved:
                if (mouseButtonPressed) {
                    sf::Vector2i v = sf::Mouse::getPosition();
                    mousePositionWhenMovedDiffX = mousePositionWhenPressedX - v.x;
                    mousePositionWhenMovedDiffY = mousePositionWhenPressedY - v.y;
                    this->gameData->renderWindow.setPosition(sf::Vector2i(
                        initialWindowX - mousePositionWhenMovedDiffX,
                        initialWindowY - mousePositionWhenMovedDiffY));
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    mouseButtonPressed = false;
                }
                break;
            default:
                break;
        }
    }
}

void MenuScreen::update() {

}

void MenuScreen::draw() {
    
    // TODO this-> überall löschen
    
    
    gameData->renderWindow.clear(sf::Color::White);
    
    // background
    sf::RectangleShape backgroundShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundShape.setFillColor(sf::Color(30, 39, 56));
    this->gameData->renderWindow.draw(backgroundShape);
    
    // title text
    sf::Text titleText;
    titleText.setFont(this->gameData->assetManager.getFont("menuFont"));
    titleText.setString("Spacefighters");
    titleText.setCharacterSize(25);
    titleText.setFillColor(COLOR_LIGHT_BLUE);
    titleText.setPosition(20, 12);
    this->gameData->renderWindow.draw(titleText);
    
    // menu text
    sf::Text menuText;
    menuText.setFont(this->gameData->assetManager.getFont("menuFont"));
    menuText.setString("MENU");
    menuText.setCharacterSize(100);
    menuText.setFillColor(COLOR_GREY);
    menuText.setPosition((WINDOW_WIDTH - menuText.getLocalBounds().width) / 2,  100);
    this->gameData->renderWindow.draw(menuText);
    
    // close button
    buttonClose.setRectangle(
        WINDOW_WIDTH - 47, 12, 35, 35,
        1.f, new COLOR_LIGHT_BLUE,
        new COLOR_DARK_BLUE);
    buttonClose.setText(
        30, new std::string("x"),
        &this->gameData->assetManager.getFont("menuFont"),
        new COLOR_LIGHT_BLUE);
    buttonClose.renderButtonOnWindow(this->gameData->renderWindow);
    
    
    // sound button
    SpaceButton buttonSound;
    buttonSound.setRectangle(
        WINDOW_WIDTH - 90, 12, 35, 35,
        1.f, new COLOR_LIGHT_BLUE,
        new COLOR_DARK_BLUE);
    buttonSound.setTexture(&this->gameData->assetManager.getTexture("soundOn"));
    buttonSound.setText(
        30, new std::string(""),
        &this->gameData->assetManager.getFont("menuFont"),
        new COLOR_LIGHT_BLUE);
    buttonSound.renderButtonOnWindow(this->gameData->renderWindow);
    
    // border around window
    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10));
    borderShape.setFillColor(sf::Color(255, 255, 255, 0));
    borderShape.setOutlineThickness(5.f);
    borderShape.setOutlineColor(COLOR_DARK_BLUE);
    borderShape.setPosition(5.f, 5.f);
    this->gameData->renderWindow.draw(borderShape);
    
    // top border
    sf::RectangleShape borderShape2(sf::Vector2f(WINDOW_WIDTH - 10, 0));
    borderShape2.setFillColor(sf::Color(129, 129, 129));
    borderShape2.setOutlineThickness(1.f);
    borderShape2.setOutlineColor(COLOR_LIGHT_BLUE);
    borderShape2.setPosition(5.f, 54.f);
    this->gameData->renderWindow.draw(borderShape2);
    
    // player vs. computer button
    SpaceButton buttonPlayerVsComputer;
    buttonPlayerVsComputer.setRectangle(
        50, 300, WINDOW_WIDTH - 100, 50,
        2.f, new COLOR_LIGHT_BLUE,
        new COLOR_DARK_BLUE);
    buttonPlayerVsComputer.setText(
        30, new std::string("Player vs. Computer"),
        &this->gameData->assetManager.getFont("menuFont"),
        new COLOR_LIGHT_BLUE);
    buttonPlayerVsComputer.renderButtonOnWindow(this->gameData->renderWindow);
    
    // player vs. player button
    SpaceButton buttonPlayerVsPlayer;
    buttonPlayerVsPlayer.setRectangle(
        50, 370, WINDOW_WIDTH - 100, 50,
        2.f, new COLOR_LIGHT_BLUE,
        new COLOR_DARK_BLUE);
    buttonPlayerVsPlayer.setText(
        30, new std::string("Player vs. Player"),
        &this->gameData->assetManager.getFont("menuFont"),
        new COLOR_LIGHT_BLUE);
    buttonPlayerVsPlayer.renderButtonOnWindow(this->gameData->renderWindow);
    
    // highscore button
    SpaceButton buttonHighscore;
    buttonHighscore.setRectangle(
        50, 440, WINDOW_WIDTH - 100, 50,
        2.f, new COLOR_LIGHT_BLUE,
        new COLOR_DARK_BLUE);
    buttonHighscore.setText(
        30, new std::string("Highscore"),
        &this->gameData->assetManager.getFont("menuFont"),
        new COLOR_LIGHT_BLUE);
    buttonHighscore.renderButtonOnWindow(this->gameData->renderWindow);
    
    // about button
    SpaceButton buttonAbout;
    buttonAbout.setRectangle(
        50, 510, WINDOW_WIDTH - 100, 50,
        2.f, new COLOR_LIGHT_BLUE,
        new COLOR_DARK_BLUE);
    buttonAbout.setText(
        30, new std::string("About"),
        &this->gameData->assetManager.getFont("menuFont"),
        new COLOR_LIGHT_BLUE);
    buttonAbout.renderButtonOnWindow(this->gameData->renderWindow);
    
    this->gameData->renderWindow.display();
}

void MenuScreen::resume() {

}

void MenuScreen::pause() {

}