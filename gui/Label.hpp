#pragma once 

#include <SFML/Graphics.hpp>

#include "UserInterface.hpp"

class Label: public UserInterface {
private:
    sf::Text m_text;
    std::string m_labelText;

    sf::Color m_originalColor = {57, 62, 67, 255};
    sf::Color m_labelColor = m_originalColor;

public:
    Label(const sf::Font& font, const sf::Vector2f& pos, const float size, const std::string& labelText);

    void setLabel(const std::string& label);
    void setMode(Mode mode) override;

    void draw(sf::RenderWindow& surface) override;
};