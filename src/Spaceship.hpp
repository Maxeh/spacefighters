//
// Created by Maximilian on 25.03.2020.
//

#ifndef SPACEFIGHTERS_SPACESHIP_HPP
#define SPACEFIGHTERS_SPACESHIP_HPP


class Spaceship {
    int x;
public:
    explicit Spaceship(int x) : x(x) {};
    void moveX(int x);
    int getX() const;
};


#endif //SPACEFIGHTERS_SPACESHIP_HPP
