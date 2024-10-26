#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <map>


class AssetManager {
private:
    std::map<std::string, sf::Texture> m_textures;
    std::map<std::string, sf::Sprite> m_sprites;
    std::map<std::string, sf::Font> m_fonts;

public:
    AssetManager();

    void loadFromFile(const std::string& filePath);

    void loadTexture(const std::string& name, const std::string& path);
    void loadSprite(const std::string& name, const sf::Texture& texture);
    void loadFont(const std::string& name, const std::string& path);

    sf::Texture& getTexture(const std::string& name);
    sf::Sprite& getSprite(const std::string& name);
    sf::Font& getFont(const std::string& name);
};