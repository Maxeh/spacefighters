#include "AssetManager.hpp"

void AssetManager::loadTexture(const std::string& name, const std::string& fileName, bool smooth) {

    sf::Texture texture;
    if (texture.loadFromFile(fileName)) {
        texture.setSmooth(smooth);
        this->texturesMap[name] = texture;
    }
}

sf::Texture &AssetManager::getTexture(const std::string& name) {
    
    return this->texturesMap.at(name);
}

void AssetManager::loadFont(const std::string& name, const std::string& fileName) {
    
    sf::Font font;
    if (font.loadFromFile(fileName)) {
        this->fontsMap[name] = font;
    }
}

sf::Font &AssetManager::getFont(const std::string& name) {
    
    return this->fontsMap.at(name);
}

void AssetManager::loadSound(const std::string& name, const std::string& fileName) {

    sf::Sound sound;
    auto* soundBuffer = new sf::SoundBuffer;
    if (soundBuffer->loadFromFile(fileName)) {
        sound.setBuffer(*soundBuffer);
        this->soundsMap[name] = sound;
    }
}

void AssetManager::playSound(const std::string &name) {

    this->soundsPlayingMap[name] = true;
    this->soundsMap[name].setLoop(true);
    this->soundsMap[name].play();
}

void AssetManager::stopSound(const std::string &name) {

    this->soundsPlayingMap[name] = false;
    this->soundsMap[name].stop();
}

void AssetManager::freeResources() {

    for (std::pair<std::string, sf::Sound> sound : this->soundsMap) {
        delete sound.second.getBuffer();
    }
    this->soundsMap.erase(this->soundsMap.begin(), this->soundsMap.end());
    this->soundsPlayingMap.erase(this->soundsPlayingMap.begin(), this->soundsPlayingMap.end());
    this->texturesMap.erase(this->texturesMap.begin(), this->texturesMap.end());
    this->fontsMap.erase(this->fontsMap.begin(), this->fontsMap.end());
}

bool AssetManager::isSoundPlaying(const std::string& name) {

    return soundsPlayingMap[name];
}
