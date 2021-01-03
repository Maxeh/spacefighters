#ifndef SPACEFIGHTERS_ASSETMANAGER_HPP
#define SPACEFIGHTERS_ASSETMANAGER_HPP

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager {

public:
    AssetManager() = default;
    ~AssetManager() = default;
    void loadTexture(const std::string& name, const std::string& fileName, bool smooth);
    sf::Texture &getTexture(const std::string& name);
    void loadFont(const std::string& name, const std::string& fileName);
    sf::Font &getFont(const std::string& name);
    void loadSound(const std::string& name, const std::string& fileName);
    void playSound(const std::string& name);
    void stopSound(const std::string& name);
    bool isSoundPlaying(const std::string& name);
    void freeResources();
private:
    std::map<std::string, sf::Texture> texturesMap;
    std::map<std::string, sf::Font> fontsMap;
    std::map<std::string, sf::Sound> soundsMap;
    std::map<std::string, bool> soundsPlayingMap;
};

#endif