#include <iostream>
#include <SFML/Audio.hpp>
#include "MenuScreen.hpp"
#include "../Constants.hpp"
#include "../SpaceButton.hpp"
#include "../GameScreen/GameScreen.hpp"

MenuScreen::MenuScreen(std::shared_ptr<GameManager::GameData> gameData) : gameData(gameData) {

    singlePlayerButton = new SpaceButton(50, 300, WINDOW_WIDTH - 100, 50);
    twoPlayerButton = new SpaceButton(50, 370, WINDOW_WIDTH - 100, 50);
    highscoreButton = new SpaceButton(50, 440, WINDOW_WIDTH - 100, 50);
    aboutButton = new SpaceButton(50, 510, WINDOW_WIDTH - 100, 50);
    closeButton = new SpaceButton(WINDOW_WIDTH - 47, 12, 35, 35);
    soundButton = new SpaceButton(WINDOW_WIDTH - 90, 12, 35, 35);
    soundButtonSprite = new sf::Sprite;
    
    gameData->assetManager.loadTexture("backgroundImage", "res/background_menu.png", false);
    gameData->assetManager.loadTexture("soundOn", "res/soundOn.png", false);
    gameData->assetManager.loadTexture("soundOff", "res/soundOff.png", true);
    gameData->assetManager.loadFont("menuFont", "res/space_age.ttf");
}

MenuScreen::~MenuScreen() {

    std::cout << "called";
    delete singlePlayerButton;
    delete twoPlayerButton;
    delete highscoreButton;
    delete aboutButton;
    delete closeButton;
    delete soundButton;
    delete soundButtonSprite;
}

void MenuScreen::init() {

    this->gameData->assetManager.loadSound(MENU_SOUND, "res/spaceSound3.wav");
    this->gameData->assetManager.playSound(MENU_SOUND);
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
                            this->gameData->assetManager.stopSound(MENU_SOUND);
                        } else {
                            soundOn = true;
                            this->gameData->assetManager.playSound(MENU_SOUND);
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

void MenuScreen::draw() {
    
    gameData->renderWindow.clear(sf::Color::White);
    
    // background
    sf::RectangleShape backgroundShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    backgroundShape.setTexture(&this->gameData->assetManager.getTexture("backgroundImage"));
    backgroundShape.setFillColor(COLOR_BLUE);
    gameData->renderWindow.draw(backgroundShape);
    
    // border around window
    sf::RectangleShape borderShape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 10));
    borderShape.setFillColor(sf::Color(255, 255, 255, 0));
    borderShape.setOutlineThickness(5.f);
    borderShape.setOutlineColor(COLOR_DARK_BLUE_1);
    borderShape.setPosition(5.f, 5.f);
    gameData->renderWindow.draw(borderShape);
    
    // top border
    sf::RectangleShape borderShape2(sf::Vector2f(WINDOW_WIDTH - 10, 0));
    borderShape2.setFillColor(sf::Color(129, 129, 129));
    borderShape2.setOutlineThickness(1.f);
    borderShape2.setOutlineColor(COLOR_LIGHT_BLUE);
    borderShape2.setPosition(5.f, 54.f);
    gameData->renderWindow.draw(borderShape2);
    
    // title text
    sf::Text titleText;
    titleText.setFont(gameData->assetManager.getFont("menuFont"));
    titleText.setString("spacefighters");
    titleText.setCharacterSize(25);
    titleText.setFillColor(COLOR_LIGHT_BLUE);
    titleText.setPosition(20, 12);
    gameData->renderWindow.draw(titleText);
    
    // menu text
    sf::Text menuText;
    menuText.setFont(gameData->assetManager.getFont("menuFont"));
    menuText.setString("MENU");
    menuText.setCharacterSize(100);
    menuText.setFillColor(COLOR_LIGHT_BLUE);
    menuText.setPosition((WINDOW_WIDTH - menuText.getLocalBounds().width) / 2,  100);
    menuText.setOutlineColor(COLOR_DARK_BLUE_1);
    menuText.setOutlineThickness(5.f);
    gameData->renderWindow.draw(menuText);
    
    // close button
    closeButton->setOutline(closeButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE, 1.f);
    closeButton->setFillColor(new COLOR_DARK_BLUE_1);
    closeButton->setFont(&gameData->assetManager.getFont("menuFont"));
    closeButton->setText(new std::string("x"), 30);
    closeButton->setTextColor(closeButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE);
    closeButton->renderButtonOnWindow(gameData->renderWindow);

    // sound button
    soundButton->setOutline(soundButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE, 1.f);
    soundButton->setFillColor(new COLOR_DARK_BLUE_1);
    std::string soundIcon = soundOn ? "soundOn" : "soundOff";
    sf::Texture& soundTexture = gameData->assetManager.getTexture(soundIcon);
    soundButtonSprite->setTexture(soundTexture);
    soundButton->setSprite(soundButtonSprite);
    soundButton->setSpriteColor(soundButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE);
    soundButton->renderButtonOnWindow(gameData->renderWindow);

    // singlePlayerButton
    singlePlayerButton->setOutline(singlePlayerButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE, 2.f);
    singlePlayerButton->setFillColor(new COLOR_DARK_BLUE_1);
    singlePlayerButton->setFont(&gameData->assetManager.getFont("menuFont"));
    singlePlayerButton->setText(new std::string("player vs. computer"), 30);
    singlePlayerButton->setTextColor(singlePlayerButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE);
    singlePlayerButton->renderButtonOnWindow(gameData->renderWindow);

    // singlePlayerButton
    twoPlayerButton->setOutline(twoPlayerButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE, 2.f);
    twoPlayerButton->setFillColor(new COLOR_DARK_BLUE_1);
    twoPlayerButton->setFont(&gameData->assetManager.getFont("menuFont"));
    twoPlayerButton->setText(new std::string("player vs. player"), 30);
    twoPlayerButton->setTextColor(twoPlayerButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE);
    twoPlayerButton->renderButtonOnWindow(gameData->renderWindow);

    // highscore button
    highscoreButton->setOutline(highscoreButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE, 2.f);
    highscoreButton->setFillColor(new COLOR_DARK_BLUE_1);
    highscoreButton->setFont(&gameData->assetManager.getFont("menuFont"));
    highscoreButton->setText(new std::string("highscore"), 30);
    highscoreButton->setTextColor(highscoreButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE);
    highscoreButton->renderButtonOnWindow(gameData->renderWindow);

    // about button
    aboutButton->setOutline(aboutButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE, 2.f);
    aboutButton->setFillColor(new COLOR_DARK_BLUE_1);
    aboutButton->setFont(&gameData->assetManager.getFont("menuFont"));
    aboutButton->setText(new std::string("about"), 30);
    aboutButton->setTextColor(aboutButtonHovered ? new COLOR_RED : new COLOR_LIGHT_BLUE);
    aboutButton->renderButtonOnWindow(gameData->renderWindow);

    gameData->renderWindow.display();
}

void MenuScreen::resume() {

}

void MenuScreen::pause() {

}