#include <SFML/Window.hpp>
#include "src/Constants.hpp"
#include "src/Model.hpp"
#include "src/View.hpp"
#include "src/Controller.hpp"

int main()
{
    srand(time(nullptr));
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Spacefighters", sf::Style::None);
    window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y - 20));
    
    Model model;
    View view(window, model);
    Controller controller(model, view);
    controller.eventLoop();
    return 0;
}