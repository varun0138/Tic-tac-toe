#pragma once 

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>

#include "UserInterface.hpp"

class Label: public UserInterface {
private:
    sf::Text m_text;
    std::string m_labelText;

    sf::Color m_labelColor;

public:
    Label(const sf::Font& font, const sf::Vector2f& pos, float size, const std::string& labelText, Mode mode);

    void setLabel(const std::string& label);
    
    void setMode(Mode mode) override;
    void draw(sf::RenderWindow& surface) override;
};