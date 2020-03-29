#ifndef SPACEFIGHTERS_VIEW_HPP
#define SPACEFIGHTERS_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Model.hpp"

class View {
    sf::RenderWindow &window;
    const Model &model;
    double rotation = 0.f;
    sf::Texture backgroundTexture;
    sf::Texture asteroidTexture;
    sf::Texture spaceshipTexture;
public:
    explicit View(sf::RenderWindow &window, const Model &model);
    void renderView();
    sf::RenderWindow &getMainWindow() const;
private:
    void renderBorder() const;
    void renderBackground() const;
    void renderAsteroids() const;
    void renderSpaceship() const;
};

#endif