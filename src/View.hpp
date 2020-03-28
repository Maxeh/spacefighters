#ifndef SFML1_VIEW_HPP
#define SFML1_VIEW_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Model.hpp"

class View {
    sf::RenderWindow &window;
    const Model &model;
    const int windowWidth;
    const int windowHeight;
    double rotation = 0.f;
    sf::Texture backgroundTexture;
    sf::Texture asteroidTexture;
    sf::Texture spaceshipTexture;
public:
    explicit View(sf::RenderWindow &window, const Model &model, const int &windowWidth, const int &windowHeight) :
        window(window), model(model), windowWidth(windowWidth), windowHeight(windowHeight) {

        backgroundTexture.loadFromFile("res/bg3.jpg");
        asteroidTexture.loadFromFile("res/asteroid-60x54.png");
        asteroidTexture.setSmooth(true);
        spaceshipTexture.loadFromFile("res/spaceship-75x74.png");
    };
    void renderView();
private:
    void renderBorder() const;
    void renderBackground() const;
    void renderAsteroids() const;
    void renderSpaceship() const;
};

#endif