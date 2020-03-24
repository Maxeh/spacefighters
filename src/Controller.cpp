#include "Controller.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

bool isPauseKey(const sf::Keyboard::Key &key) {

    return key == sf::Keyboard::P;
}

//bool isDirectionKey(const sf::Keyboard::Key &key) {
//
//    return key == sf::Keyboard::Up || key == sf::Keyboard::Down || key == sf::Keyboard::Left ||
//           key == sf::Keyboard::Right;
//}

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

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
//                    if (isDirectionKey(event.key.code)) {
//                        model.setMoveDirection(convertDirectionKey(event.key.code));
//                    }
//                    if (isPauseKey(event.key.code)) {
//                        pause = !pause;
//                    }

                    break;
                default:
                    break;
            }
        }
//        window.setActive(false);
//        view.renderView();


        if (!pause && clock.getElapsedTime().asMilliseconds() >= 15) {
            model.moveAsteroids();
            view.renderView();
            clock.restart();
        }



    }
}