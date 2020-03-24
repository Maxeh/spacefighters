#ifndef SFML1_CONTROLLER_HPP
#define SFML1_CONTROLLER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include "Model.hpp"
#include "View.hpp"

class Controller {
    sf::RenderWindow &window;
    Model &model;
    View &view;
    bool pause;
public:
    explicit Controller(sf::RenderWindow &window, Model &model, View &view) : window(window), model(model), view(view), pause(false) {};
    void eventLoop();
};

#endif