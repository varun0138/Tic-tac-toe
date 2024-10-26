#include "Button.hpp"

Button::Button(const sf::Font& font) {
    m_text.setFont(font);
}

Button::Button(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, const std::string& label)
    : m_pos(pos), m_size(size), m_label(label) {

    m_text.setFont(font);
}

void Button::setLabel(const std::string& label) {
    m_label = label;
}

void Button::setMode(Mode mode) {
    m_fillColor    = convertMode(m_colors[0], mode);
    m_clickColor   = convertMode(m_colors[1], mode);
    m_outlineColor = convertMode(m_colors[2], mode);
    m_labelColor   = convertMode(m_colors[3], mode);
}

bool Button::buttonClicked(const sf::Vector2f& mousePos) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_buttonPressed) {
        if(mousePos.x >= m_pos.x && mousePos.x <= m_pos.x + m_size.x) {
            if(mousePos.y >= m_pos.y && mousePos.y <= m_pos.y + m_size.y) {
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
    return m_label;
}

void Button::draw(sf::RenderWindow& surface) {
    
    m_button.setPosition(m_pos);
    m_button.setSize(m_size);
    m_button.setFillColor(m_fillColor);
    m_button.setOutlineColor(m_outlineColor);
    m_button.setOutlineThickness(m_thickness);

    if(m_buttonPressed) {
        m_button.setFillColor(m_clickColor);
    }

    m_text.setString(m_label);
    m_text.setFillColor(m_labelColor);
    // m_text.setCharacterSize(std::min(m_size.x / m_label.size(), m_size.y / 2.0f));
    m_text.setCharacterSize(std::min(m_size.x, m_size.y) / 2.0f);

    const sf::FloatRect bounds = m_text.getLocalBounds();
    const sf::Vector2f labelPos = { m_pos.x + m_size.x / 2.0f - bounds.width / 2.0f - bounds.left, m_pos.y + m_size.y / 2.0f - bounds.height / 2.0f - bounds.top };
    m_text.setPosition(labelPos);
 
    surface.draw(m_button);
    surface.draw(m_text);
}

