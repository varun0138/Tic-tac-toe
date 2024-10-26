#pragma once

#include <SFML/Graphics.hpp>

#include "UserInterface.hpp"


class Button: public UserInterface {
private:
    sf::RectangleShape m_button;
    sf::Text m_text;

    sf::Vector2f m_pos  = { 10.0f, 10.0f };
    sf::Vector2f m_size = { 120.0f, 40.0f };

    sf::Color m_colors[4] = { {57, 62, 67, 255}, {146, 134, 148, 255}, {255, 255, 255, 128}, {192, 193, 195, 255} };

    sf::Color m_fillColor    = m_colors[0];
    sf::Color m_clickColor   = m_colors[1];
    sf::Color m_outlineColor = m_colors[2];
    sf::Color m_labelColor   = m_colors[3];

    float m_thickness = 2.0f;
    std::string m_label = "";
    bool m_buttonPressed = false;

public:
    Button(const sf::Font& font);
    Button(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& label);

    void setLabel(const std::string& label);
    void setMode(Mode mode) override;

    bool buttonClicked(const sf::Vector2f& mousePos);
    std::string getLabel() const;

    void draw(sf::RenderWindow& surface) override;
};