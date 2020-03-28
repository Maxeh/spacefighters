#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "src/Model.hpp"
#include "src/View.hpp"
#include "src/Controller.hpp"

int main()
{
    const int WINDOW_WIDTH = 700;
    const int WINDOW_HEIGHT = 900;
    srand(time(nullptr));
    
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Spacefighters", sf::Style::None);
    window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y - 20));

    Model model(WINDOW_WIDTH, WINDOW_HEIGHT);
    View view(window, model, WINDOW_WIDTH, WINDOW_HEIGHT);
    Controller controller(window, model, view);
    controller.eventLoop();
    return 0;
}