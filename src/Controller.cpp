#include "Controller.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

bool isPauseKey(const sf::Keyboard::Key &key) {

    return key == sf::Keyboard::P;
}

bool isDirectionKey(const sf::Keyboard::Key &key) {

    return key == sf::Keyboard::Up || key == sf::Keyboard::Down || key == sf::Keyboard::Left ||
           key == sf::Keyboard::Right;
}

//MoveDirection convertDirectionKey(const sf::Keyboard::Key &key) {
//
//    switch (key) {
//        case sf::Keyboard::Up:
//            return MoveDirection::Up;
//        case sf::Keyboard::Down:
//            return MoveDirection::Down;
//        case sf::Keyboard::Left:
//            return MoveDirection::Left;
//        case sf::Keyboard::Right:
//            return MoveDirection::Right;
//        default:
//            throw std::runtime_error("Key is not a direction key");
//    }
//}

void Controller::eventLoop() {

    bool mouseButtonPressed = false;
    int initialWindowX = 0;
    int initialWindowY = 0;
    int mousePositionWhenPressedX = 0;
    int mousePositionWhenPressedY = 0;
    int mousePositionWhenMovedDiffX = 0;
    int mousePositionWhenMovedDiffY = 0;

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Left) {
                        model.moveSpaceship(model.MoveDirection::Left);
                    }
                    if (event.key.code == sf::Keyboard::Right) {
                        model.moveSpaceship(model.MoveDirection::Right);
                    }
                    if (isPauseKey(event.key.code)) {
                        pause = !pause;
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        initialWindowX = window.getPosition().x;
                        initialWindowY = window.getPosition().y;
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
                        window.setPosition(sf::Vector2i(
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

        if (!pause && clock.getElapsedTime().asMilliseconds() >= 15) {
            model.moveAsteroids();
            model.rotateAsteroids();
            view.renderView();
            clock.restart();
        }
    }
}