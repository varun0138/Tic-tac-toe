#include <SFML/Window/Mouse.hpp>

#include "Button.hpp"

Button::Button(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, float thickness, const std::string& label, Mode mode) {
    m_button.setPosition(pos);
    m_button.setSize(size);
    m_button.setOutlineThickness(thickness);

    m_text.setFont(font);
    m_text.setCharacterSize(std::min(size.x, size.y) / 2.0f);
    m_text.setString(label);

    const sf::FloatRect bounds  = m_text.getLocalBounds();
    const sf::Vector2f labelPos = { pos.x + size.x / 2.0f - bounds.width  / 2.0f - bounds.left, 
                                    pos.y + size.y / 2.0f - bounds.height / 2.0f - bounds.top };
    m_text.setPosition(labelPos);

    m_colors["Fill Color"]    = {57,  62,  67,  255};
    m_colors["Click Color"]   = {146, 134, 148, 255};
    m_colors["Outline Color"] = {255, 255, 255, 128};
    m_colors["Label Color"]   = {192, 193, 195, 255};

    if(mode == LIGHT) {
        setMode(mode);
    }
}

void Button::setMode(Mode mode) {
    m_colors["Fill Color"]    = convertMode(m_colors["Fill Color"]);
    m_colors["Click Color"]   = convertMode(m_colors["Fill Color"]);
    m_colors["Outline Color"] = convertMode(m_colors["Fill Color"]);
    m_colors["Label Color"]   = convertMode(m_colors["Fill Color"]);
}

bool Button::buttonClicked(const sf::Vector2i& mousePos) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_buttonPressed) {
        if(m_button.getGlobalBounds().contains((sf::Vector2f)mousePos)) {
            m_buttonPressed = true;
            return true;
        }
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_buttonPressed) {
        m_buttonPressed = false;
    }
    return false;
}

std::string Button::getLabel() const {
    return m_text.getString();
}

void Button::draw(sf::RenderWindow& surface) {
    // BUTTON
    m_button.setFillColor(m_buttonPressed ? m_colors["Click Color"]:  m_colors["Fill Color"]);
    m_button.setOutlineColor(m_colors["Outline Color"]);
    surface.draw(m_button);

    // LABEL
    m_text.setFillColor(m_colors["Label Color"]);
    surface.draw(m_text);
}