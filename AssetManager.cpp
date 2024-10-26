#include "AssetManager.hpp"

#include <iostream>
#include <fstream>

AssetManager::AssetManager() {}

void AssetManager::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if(!file) {
        std::cerr << "Error loading file: " << filePath << std::endl;
        return;
    }

    while(!file.eof()) {      
        std::string type, name, path;
        file >> type >> name >> path;
        if(type == "Texture") {
            loadTexture(name, path);
            loadSprite(name, getTexture(name));
        }
        else if(type == "Font") {
            loadFont(name, path);
        }
        else {
            std::cout << "Type Not Found!" << std::endl;
        }
    }

    file.close();
}

void AssetManager::loadTexture(const std::string& name, const std::string& path) {
    sf::Texture texture;
    if(!texture.loadFromFile(path)) {
        std::cerr << "Texture not loaded!" << std::endl;
        return;
    }
    m_textures[name] = texture;
    std::cout << "Texture loaded from: " << path << std::endl;
}

void AssetManager::loadSprite(const std::string& name, const sf::Texture& texture) {
    sf::Sprite sprite;
    sprite.setTexture(texture);

    m_sprites[name] = sprite;
}

void AssetManager::loadFont(const std::string& name, const std::string& path) {
    sf::Font font;
    if(!font.loadFromFile(path)) {
        std::cerr << "Font not loaded!" << std::endl;
        return;
    }
    m_fonts[name] = font;
    std::cout << "Font loaded from: " << path << std::endl;
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    return m_textures.at(name);
}

sf::Sprite& AssetManager::getSprite(const std::string& name) {
    return m_sprites.at(name);
}

sf::Font& AssetManager::getFont(const std::string& name) {
    return m_fonts.at(name);
}