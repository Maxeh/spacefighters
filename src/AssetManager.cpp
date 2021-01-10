#include "AssetManager.hpp"

void AssetManager::loadTexture(const std::string& name, const std::string& fileName, bool smooth) {

    sf::Texture texture;
    if (texture.loadFromFile(fileName)) {
        texture.setSmooth(smooth);
        texturesMap[name] = texture;
    }
}

sf::Texture& AssetManager::getTexture(const std::string& name) {

    return texturesMap.at(name);
}

void AssetManager::loadFont(const std::string& name, const std::string& fileName) {

    sf::Font font;
    if (font.loadFromFile(fileName)) {
        fontsMap[name] = font;
    }
}

sf::Font& AssetManager::getFont(const std::string& name) {

    return fontsMap.at(name);
}

void AssetManager::loadSound(const std::string& name, const std::string& fileName) {

    sf::Sound sound;
    auto* soundBuffer = new sf::SoundBuffer;
    if (soundBuffer->loadFromFile(fileName)) {
        sound.setBuffer(*soundBuffer);
        soundsMap[name] = sound;
    }
}

void AssetManager::playSound(const std::string& name) {

    soundsPlayingMap[name] = true;
    soundsMap[name].setLoop(true);
    soundsMap[name].play();
}

void AssetManager::stopSound(const std::string& name) {

    soundsPlayingMap[name] = false;
    soundsMap[name].stop();
}

void AssetManager::freeResources() {

    for (std::pair<std::string, sf::Sound> sound : soundsMap) {
        delete sound.second.getBuffer();
    }
    soundsMap.erase(soundsMap.begin(), soundsMap.end());
    soundsPlayingMap.erase(soundsPlayingMap.begin(), soundsPlayingMap.end());
    texturesMap.erase(texturesMap.begin(), texturesMap.end());
    fontsMap.erase(fontsMap.begin(), fontsMap.end());
}

bool AssetManager::isSoundPlaying(const std::string& name) {

    return soundsPlayingMap[name];
}
