#include "ScreenManager.hpp"

void ScreenManager::addScreen(std::unique_ptr<Screen> newScreen_, bool isReplacing_) {

    isAdding = true;
    isReplacing = isReplacing_;
    newScreen = std::move(newScreen_);
}

void ScreenManager::removeScreen() {
    
    isRemoving = true;
}

void ScreenManager::processScreenChanges() {

//    if (isRemoving && !screens.empty()) {
//        screens.pop();
//        if (!screens.empty()) {
//            screens.top()->resume();
//        }
//        isRemoving = false;
//    }
    
    if (isAdding) {
        if (!screens.empty()) {
            if (isReplacing) {
                screens.pop();
            } //else {
//                screens.top()->pause();
//            }
        }
        
        screens.push(std::move(newScreen));
        screens.top()->init();
        isAdding = false;
    }
}

std::unique_ptr<Screen> &ScreenManager::getActiveScreen() {
    
    return screens.top();
}