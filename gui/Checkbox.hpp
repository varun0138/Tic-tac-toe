#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>

#include "UserInterface.hpp"

class Checkbox: public UserInterface {
private:
    sf::RectangleShape m_box;
    sf::RectangleShape m_checkbox;
    sf::Text m_text;

    std::map<std::string, sf::Color> m_colors;

    bool m_checked = false;
    bool m_mousePressed = false;

public:
    Checkbox(const sf::Font& font, const sf::Vector2f& pos, float size, float thickness, const std::string& label, Mode mode);

    void setCheck(const sf::Vector2f& mousePos);
    void setMode(Mode mode) override;

    bool isbuttonChecked() const;

    void draw(sf::RenderWindow& surface) override;
};