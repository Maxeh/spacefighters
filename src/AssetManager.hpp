#ifndef SPACEFIGHTERS_ASSETMANAGER_HPP
#define SPACEFIGHTERS_ASSETMANAGER_HPP

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class AssetManager {

public:
    AssetManager() = default;
    ~AssetManager() = default;
    void loadTexture(const std::string& name, const std::string& fileName);
    sf::Texture &getTexture(const std::string& name);
    void loadFont(const std::string& name, const std::string& fileName);
    sf::Font &getFont(const std::string& name);
private:
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::Font> fonts;
};

#endif