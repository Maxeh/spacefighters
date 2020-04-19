#include "AssetManager.hpp"

void AssetManager::loadTexture(const std::string& name, const std::string& fileName) {

    sf::Texture texture;
    if (texture.loadFromFile(fileName)) {
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