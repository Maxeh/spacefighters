#ifndef SPACEFIGHTERS_ASTEROID_HPP
#define SPACEFIGHTERS_ASTEROID_HPP

class Asteroid {
private:
    static constexpr float VELOCITY = 2;
    float x;
    float y;
    float angle;
    float rotation;
    bool visible = true;
public:
    static constexpr float ASTEROID_WIDTH = 60;
    static constexpr float ASTEROID_HEIGHT = 54;
    explicit Asteroid(float x, float y, float rotation);
    float getX() const;
    float getY() const;
    float getRotation() const;
    bool isVisible() const;
    void setVisible(bool _visible);
    void rotate();
    void move();
};

#endif