#include <SFML/Window/Mouse.hpp>

#include "Checkbox.hpp"

Checkbox::Checkbox(const sf::Font& font, const sf::Vector2f& pos, float size, float thickness, const std::string& label, Mode mode) {
    m_box.setPosition(pos);
    m_box.setSize(sf::Vector2f(size, size));
    m_box.setOutlineThickness(thickness);

    const float PADDING = size * 0.3f;

    m_checkbox.setPosition(pos + sf::Vector2f(PADDING / 2.0f, PADDING / 2.0f));
    m_checkbox.setSize(sf::Vector2f(size - PADDING, size - PADDING));

    m_text.setFont(font);
    m_text.setString(label);
    m_text.setCharacterSize(size / 2.0f);

    const sf::FloatRect bounds = m_text.getLocalBounds();
    const sf::Vector2f labelPos = { pos.x + size + 10.0f, pos.y + size / 2.0f - bounds.height / 2.0f - bounds.top };
    m_text.setPosition(labelPos);
    
    m_colors["Fill Color"]    = {0, 0, 0, 128};
    m_colors["Check Color"]   = {57, 62, 67, 255};
    m_colors["Outline Color"] = {255, 255, 255, 128};
    m_colors["Label Color"]   = {192, 193, 195, 255};

    if(mode == LIGHT) {
        setMode(mode);
    }
}


void Checkbox::setMode(Mode mode) {
    m_colors["Fill Color"]    = convertMode(m_colors["Fill Color"]);
    m_colors["Check Color"]   = convertMode(m_colors["Check Color"]);
    m_colors["Outline Color"] = convertMode(m_colors["Outline Color"]);
    m_colors["Label Color"]   = convertMode(m_colors["Label Color"]);
}

void Checkbox::setCheck(const sf::Vector2f& mousePos) {
    const sf::Vector2f pos = m_box.getPosition();
    const float size = m_box.getSize().x;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(!m_mousePressed) {
            if(mousePos.x >= pos.x && mousePos.x <= pos.x + size) {
                if(mousePos.y >= pos.y && mousePos.y <= pos.y + size) {
                    m_checked = !m_checked;
                    m_mousePressed = true;
                }
            }
        } 
    }
    else if(m_mousePressed) {
        m_mousePressed = false;
    }
}

bool Checkbox::isbuttonChecked() const {
    return m_checked;
}

void Checkbox::draw(sf::RenderWindow& surface) {
    // CHECK BOX
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(surface);
    setCheck(mousePos);

    m_box.setFillColor(m_colors["Fill Color"]);
    m_box.setOutlineColor(m_colors["Outline Color"]);
    surface.draw(m_box);

    // CHECK
    if(m_checked) {
        m_checkbox.setFillColor(m_colors["Check Color"]);
        surface.draw(m_checkbox);
    } 

    // LABEL
    m_text.setFillColor(m_colors["Label Color"]);
    surface.draw(m_text);
}