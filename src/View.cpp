#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Constants.hpp"
#include "View.hpp"

View::View(sf::RenderWindow &window, const Model &model) : window(window), model(model) {
    
    backgroundTexture.loadFromFile("res/bg3.jpg");
    asteroidTexture.loadFromFile("res/asteroid-60x54.png");
    asteroidTexture.setSmooth(true);
    spaceshipTexture.loadFromFile("res/spaceship-75x74.png");
}

void View::renderView() {
    
    window.clear(sf::Color::White);
    
    renderBackground();
    renderAsteroids();
    renderSpaceship();
    renderBorder();
    
    window.display();
    rotation = rotation + 2.0;
}

void View::renderBackground() const {
    
    sf::RectangleShape shape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    shape.setTexture(&backgroundTexture);
    window.draw(shape);
}

void View::renderBorder() const {
    
    sf::RectangleShape shape(sf::Vector2f(WINDOW_WIDTH - 10, WINDOW_HEIGHT - 20));
    shape.setFillColor(sf::Color(255, 255, 255, 0));
    shape.setOutlineThickness(5.f);
    shape.setOutlineColor(sf::Color(200, 100, 0));
    shape.setPosition(5.f, 15.f);
    window.draw(shape);
}

void View::renderAsteroids() const {
    
    for (const Asteroid &asteroid : model.getAsteroids()) {
        sf::Sprite sprite;
        sprite.setOrigin((float) model.getAsteroidWidth() / 2, (float) model.getAsteroidHeight() / 2);
        sprite.setTexture(asteroidTexture);
        sprite.setPosition(
            (float) asteroid.getX() + (float) model.getAsteroidWidth() / 2,
            (float) asteroid.getY() + (float) model.getAsteroidHeight() / 2);
        sprite.rotate(asteroid.getRotation());
        window.draw(sprite);
    }
}

void View::renderSpaceship() const {
    
    sf::Sprite sprite;
    sprite.setTexture(spaceshipTexture);
    sprite.setPosition(model.getSpaceship().getX(), (float) WINDOW_HEIGHT - 100);
    window.draw(sprite);
}

sf::RenderWindow &View::getMainWindow() const {
    
    return window;
}