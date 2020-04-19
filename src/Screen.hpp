#ifndef SPACEFIGHTERS_SCREEN_HPP
#define SPACEFIGHTERS_SCREEN_HPP

class Screen {
public:
    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void resume() = 0;
    virtual void pause() = 0;
};

#endif