#include "ScreenManager.hpp"

void ScreenManager::addScreen(std::unique_ptr<Screen> newScreen, bool isReplacing) {

    this->isAdding = true;
    this->isReplacing = isReplacing;
    this->newScreen = std::move(newScreen);
}

void ScreenManager::removeScreen() {
    
    this->isRemoving = true;
}

void ScreenManager::processScreenChanges() {

    if (this->isRemoving && !this->screens.empty()) {
        this->screens.pop();
        if (!this->screens.empty()) {
            this->screens.top()->resume();
        }
        this->isRemoving = false;
    }
    
    if (this->isAdding) {
        if (!this->screens.empty()) {
            if (this->isReplacing) {
                this->screens.pop();
            } else {
                this->screens.top()->pause();
            }
        }
        
        this->screens.push(std::move(this->newScreen));
        this->screens.top()->init();
        this->isAdding = false;
    }
}

std::unique_ptr<Screen> &ScreenManager::getActiveScreen() {
    
    return this->screens.top();
}