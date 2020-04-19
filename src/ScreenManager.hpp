#ifndef SPACEFIGHTERS_SCREENMANAGER_HPP
#define SPACEFIGHTERS_SCREENMANAGER_HPP

#include <memory>
#include <stack>
#include "Screen.hpp"

class ScreenManager {
private:
    std::stack<std::unique_ptr<Screen>> screens;
    std::unique_ptr<Screen> newScreen;
    bool isRemoving;
    bool isAdding;
    bool isReplacing;
public:
    ScreenManager() = default;
    ~ScreenManager() = default;
    void addScreen(std::unique_ptr<Screen> newScreen, bool isReplacing = true);
    void removeScreen();
    void processScreenChanges();
    std::unique_ptr<Screen> &getActiveScreen();
};

#endif