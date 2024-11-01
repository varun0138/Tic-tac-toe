#pragma once 

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>

#include "UserInterface.hpp"

class Label: public UserInterface {
private:
    sf::Text m_text;
    sf::Color m_color;

public:
    std::string caption;

    Label(const sf::Font& font, const sf::Vector2f& pos, float size, const std::string& cap, Mode mode);
    
    void setMode(Mode mode) override;
    void draw(sf::RenderWindow& surface) override;
};