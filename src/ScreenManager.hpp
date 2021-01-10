#ifndef SPACEFIGHTERS_SCREENMANAGER_HPP
#define SPACEFIGHTERS_SCREENMANAGER_HPP

#include <memory>
#include <stack>
#include "Screen.hpp"

class ScreenManager {
    bool isRemoving = false;
    bool isAdding = false;
    bool isReplacing = false;
    std::stack<std::unique_ptr<Screen>> screens;
    std::unique_ptr<Screen> newScreen;
public:
    ScreenManager() = default;
    ~ScreenManager() = default;
    void addScreen(std::unique_ptr<Screen> newScreen, bool isReplacing = true);
    void removeScreen();
    void processScreenChanges();
    std::unique_ptr<Screen>& getActiveScreen();
};

#endif