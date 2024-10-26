#include "Label.hpp"

Label::Label(const sf::Font& font, const sf::Vector2f& pos, const float size, const std::string& labelText) {
    m_text.setFont(font);
    m_text.setPosition(pos);
    m_text.setCharacterSize(size);
    m_labelText = labelText;
}

void Label::setLabel(const std::string& label) {
    m_labelText = label;
}

void Label::setMode(Mode mode) {
    m_labelColor = convertMode(m_originalColor, mode);
}

void Label::draw(sf::RenderWindow& surface) {
    m_text.setString(m_labelText);
    m_text.setFillColor(m_labelColor);
    surface.draw(m_text);
}