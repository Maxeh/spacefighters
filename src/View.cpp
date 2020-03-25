#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "View.hpp"

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

    sf::RectangleShape shape(sf::Vector2f(windowWidth, windowHeight));
    shape.setTexture(&backgroundTexture);
//    shape.setPosition(5.f, 5.f);
    window.draw(shape);
}

void View::renderBorder() const {

    sf::RectangleShape shape(sf::Vector2f(windowWidth-10, windowHeight-20));
    shape.setFillColor(sf::Color(255, 255, 255, 0));
    shape.setOutlineThickness(5.f);
    shape.setOutlineColor(sf::Color(200, 100, 0));
    shape.setPosition(5.f, 15.f);
    window.draw(shape);
}

void View::renderAsteroids() const {

    for (const Asteroid &asteroid : model.getAsteroids()) {
//        sf::RectangleShape shape(sf::Vector2f(model.ASTEROID_WIDTH, model.ASTEROID_HEIGHT));
//        shape.setFillColor(sf::Color(0,0,0));
//        shape.setPosition((float) asteroid.getX(), (float) asteroid.getY());
//        window.draw(shape);
        sf::Sprite sprite;
        sprite.setOrigin(model.ASTEROID_WIDTH / 2, model.ASTEROID_HEIGHT / 2);
        sprite.setTexture(asteroidTexture);
        sprite.setPosition((float) asteroid.getX() + model.ASTEROID_WIDTH / 2, (float) asteroid.getY() + model.ASTEROID_HEIGHT / 2);
        sprite.rotate(asteroid.getRotation());
        window.draw(sprite);
    }
}

void View::renderSpaceship() const {

    sf::Sprite sprite;
    sprite.setTexture(spaceshipTexture);
    sprite.setPosition((float) model.getSpaceship().getX(), (float) windowHeight - 100);
    window.draw(sprite);
}



int View::getWindowWidth() const {
    return windowWidth;
}

int View::getWindowHeight() const {
    return windowHeight;
}

sf::RenderWindow &View::getRenderWindow() const {
    return window;
}

Model const &View::getModel() const {
    return model;
}


