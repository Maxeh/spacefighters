#ifndef SPACEFIGHTERS_CONTROLLER_HPP
#define SPACEFIGHTERS_CONTROLLER_HPP

#include "Model.hpp"
#include "View.hpp"

class Controller {
    Model &model;
    View &view;
    bool pause;
public:
    explicit Controller(Model &model, View &view);
    void eventLoop();
};

#endif