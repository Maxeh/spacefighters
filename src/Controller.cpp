#include "Controller.hpp"
#include <SFML/Window.hpp>

#include <windows.h>


Controller::Controller(Model &model, View &view) : model(model), view(view), pause(false) {};

bool isPauseKey(const sf::Keyboard::Key &key) {
    
    return key == sf::Keyboard::P;
}

void Controller::eventLoop() {
    
    int initialWindowX = 0;
    int initialWindowY = 0;
    int mousePositionWhenPressedX = 0;
    int mousePositionWhenPressedY = 0;
    int mousePositionWhenMovedDiffX = 0;
    int mousePositionWhenMovedDiffY = 0;
    float velocity = 2;
    float acceleration = 0.1;
    bool mouseButtonPressed = false;
    
    sf::Clock clockAsteroid;
    sf::Clock clockSpaceship;
    
    sf::RenderWindow &mainWin = view.getMainWindow();
    while (mainWin.isOpen()) {
        sf::Event event{};
        while (mainWin.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    mainWin.close();
                    break;
                case sf::Event::KeyPressed:
                    if (isPauseKey(event.key.code)) {
                        pause = !pause;
                        ShowWindow(mainWin.getSystemHandle(), SW_MINIMIZE);
                    }
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::Left) {
                        velocity = 2;
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        velocity = 2;
                    }
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        initialWindowX = mainWin.getPosition().x;
                        initialWindowY = mainWin.getPosition().y;
                        sf::Vector2i mousePositionVector = sf::Mouse::getPosition();
                        mousePositionWhenPressedX = mousePositionVector.x;
                        mousePositionWhenPressedY = mousePositionVector.y;
                        mouseButtonPressed = true;
                    }
                    break;
                case sf::Event::MouseMoved:
                    if (mouseButtonPressed) {
                        sf::Vector2i v = sf::Mouse::getPosition();
                        mousePositionWhenMovedDiffX = mousePositionWhenPressedX - v.x;
                        mousePositionWhenMovedDiffY = mousePositionWhenPressedY - v.y;
                        mainWin.setPosition(sf::Vector2i(
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
        
        if (!pause && clockAsteroid.getElapsedTime().asMilliseconds() >= 15) {
            model.moveAsteroids();
            model.rotateAsteroids();
            clockAsteroid.restart();
        }
        
        bool moveSpaceship = false;
        if (clockSpaceship.getElapsedTime().asMilliseconds() >= 5) {
            moveSpaceship = true;
            clockSpaceship.restart();
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (moveSpaceship) {
                model.moveSpaceship(-velocity);
                if (velocity < 5) {
                    velocity += acceleration;
                }
            }
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (moveSpaceship) {
                model.moveSpaceship(velocity);
                if (velocity < 5) {
                    velocity += acceleration;
                }
            }
        }
        
        view.renderView();
    }
}