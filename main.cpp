#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "src/Model.hpp"
#include "src/View.hpp"
#include "src/Controller.hpp"

int main()
{
    const int windowWidth = 700;
    const int windowHeight = 900;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Spacefighters",sf::Style::None);
    window.setPosition(sf::Vector2i(window.getPosition().x, window.getPosition().y - 20));

    Model model(windowWidth, windowHeight);
    View view(window, model, windowWidth, windowHeight);
    Controller controller(window, model, view);
    controller.eventLoop();
    return 0;
}