#include "Label.hpp"

Label::Label(const sf::Font& font, const sf::Vector2f& pos, float size, const std::string& cap, Mode mode) {
    m_text.setFont(font);
    m_text.setPosition(pos);
    m_text.setCharacterSize(size);
    caption = cap;

    m_color = {57, 62, 67, 255};
    if(mode == LIGHT) {
        setMode(mode);
    }
}

void Label::setMode(Mode mode) {
    m_color = convertMode(m_color);
}

void Label::draw(sf::RenderWindow& surface) {
    m_text.setString(caption);
    m_text.setFillColor(m_color);
    surface.draw(m_text);
}