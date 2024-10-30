#include "Button.hpp"

Button::Button(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& label, Mode mode) {
    m_text.setFont(font);
    setMode(mode);

    m_button.setPosition(pos);
    m_button.setSize(size);
    m_button.setOutlineThickness(m_thickness);

    m_text.setCharacterSize(std::min(size.x, size.y) / 2.0f);
    m_text.setString(label);

    const sf::FloatRect bounds  = m_text.getLocalBounds();
    const sf::Vector2f labelPos = { pos.x + size.x / 2.0f - bounds.width / 2.0f - bounds.left, pos.y + size.y / 2.0f - bounds.height / 2.0f - bounds.top };
    m_text.setPosition(labelPos);
}

void Button::setMode(Mode mode) {
    m_fillColor    = convertMode(m_colors[0], mode);
    m_clickColor   = convertMode(m_colors[1], mode);
    m_outlineColor = convertMode(m_colors[2], mode);
    m_labelColor   = convertMode(m_colors[3], mode);
}

bool Button::buttonClicked(const sf::Vector2f& mousePos) {
    const sf::Vector2f pos  = m_button.getPosition();
    const sf::Vector2f size = m_button.getSize();

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_buttonPressed) {
        if(mousePos.x >= pos.x && mousePos.x <= pos.x + size.x) {
            if(mousePos.y >= pos.y && mousePos.y <= pos.y + size.y) {
                m_buttonPressed = true;
                return true;
            }
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
    m_button.setFillColor(m_buttonPressed ? m_clickColor: m_fillColor);
    m_button.setOutlineColor(m_outlineColor);

    m_text.setFillColor(m_labelColor);

    surface.draw(m_button);
    surface.draw(m_text);
}