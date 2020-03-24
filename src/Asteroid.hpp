#ifndef SFML1_ASTEROID_HPP
#define SFML1_ASTEROID_HPP

class Asteroid {
    int x;
    int y;
public:
    Asteroid(int x, int y) : x(x), y(y) {};
    int getX();
    int getY();
    void moveX(int x);
    void moveY(int y);
};

#endif //SFML1_ASTEROID_HPP