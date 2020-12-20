#include "AssetManager.hpp"
#include <SFML/Audio.hpp>

void AssetManager::loadTexture(const std::string& name, const std::string& fileName, bool smooth) {

    sf::Texture texture;
    if (texture.loadFromFile(fileName)) {
        texture.setSmooth(smooth);
        this->textures[name] = texture;
    }
}

sf::Texture &AssetManager::getTexture(const std::string& name) {
    
    return this->textures.at(name);
}

void AssetManager::loadFont(const std::string& name, const std::string& fileName) {
    
    sf::Font font;
    if (font.loadFromFile(fileName)) {
        this->fonts[name] = font;
    }
}

sf::Font &AssetManager::getFont(const std::string& name) {
    
    return this->fonts.at(name);
}

void AssetManager::loadSound(const std::string& name, const std::string& fileName) {

    sf::Sound sound;
    auto* soundBuffer = new sf::SoundBuffer;
    if (soundBuffer->loadFromFile(fileName)) {
        sound.setBuffer(*soundBuffer);
        this->sounds[name] = sound;
    }
}

void AssetManager::playSound(const std::string &name) {

    this->sounds[name].setLoop(true);
    this->sounds[name].play();
}

void AssetManager::stopSound(const std::string &name) {

    this->sounds[name].stop();
}

void AssetManager::freeResources() {

    for (std::pair<std::string, sf::Sound> sound : this->sounds) {
        delete sound.second.getBuffer();
    }
    this->sounds.erase(this->sounds.begin(), this->sounds.end());
    this->textures.erase(this->textures.begin(), this->textures.end());
    this->fonts.erase(this->fonts.begin(), this->fonts.end());
}
