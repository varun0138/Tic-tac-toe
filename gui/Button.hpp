#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>

#include "UserInterface.hpp"

class Button: public UserInterface {
private:
    sf::RectangleShape m_button;
    sf::Text m_text;

    std::map<std::string, sf::Color> m_colors;
    bool m_buttonPressed = false;

public:
    Button(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, float thickness, const std::string& label, Mode mode);

    bool buttonClicked(const sf::Vector2i& mousePos);
    std::string getLabel() const;

    void setMode(Mode mode) override;
    void draw(sf::RenderWindow& surface) override;
};