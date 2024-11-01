#include "Dropdownbox.hpp"

Dropdownbox::Dropdownbox(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, float thickness, const std::string& label,  const std::vector<std::string>& items, Mode mode) {

    m_button.setPosition(pos);
    m_button.setSize(size);
    m_button.setOutlineThickness(thickness);

    m_text.setFont(font);
    m_text.setString(label);
    m_text.setCharacterSize(std::min(size.x, size.y) / 2.0f);
    const sf::FloatRect bounds = m_text.getLocalBounds();
    const sf::Vector2f labelPos = { pos.x + size.x / 2.0f - bounds.width  / 2.0f - bounds.left, 
                                    pos.y + size.y / 2.0f - bounds.height / 2.0f - bounds.top };
    m_text.setPosition(labelPos);

    for(unsigned int i = 0; i < items.size(); i++) {
        sf::RectangleShape itemButton;
        m_itemButtons.push_back(itemButton);

        sf::Text itemText;
        itemText.setFont(font);
        itemText.setString(items[i]);
        m_itemTexts.push_back(itemText);
    }

    m_colors["Fill Color"]    = {57,  62,  67,  255};
    m_colors["Click Color"]   = {146, 134, 148, 255};
    m_colors["Outline Color"] = {255, 255, 255, 128};
    m_colors["Label Color"]   = {192, 193, 195, 255};

    if(mode == LIGHT) {
        setMode(mode);
    }
}

void Dropdownbox::update(const sf::Vector2f& mousePos) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && !m_mousePressed) {
        if(m_button.getGlobalBounds().contains(mousePos)) {
            toggleMenu();
        }
        else if(m_isOpen) {
            for(unsigned int i = 0; i < m_itemTexts.size(); i++) {
                if(m_itemButtons[i].getGlobalBounds().contains(mousePos)) {
                    selectItem(i);
                    break;
                }
            }
        }
        m_mousePressed = true;
    }
    else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_mousePressed) {
        m_mousePressed = false;
    }
}

std::string Dropdownbox::getSelectedItem() const {
    if(m_selectedItem >= 0 && m_selectedItem < (int)m_itemTexts.size()) {
        return m_itemTexts[m_selectedItem].getString();
    }
    return "";
}

void Dropdownbox::setMode(Mode mode) {
    m_colors["Fill Color"]    = convertMode(m_colors["Fill Color"]);
    m_colors["Click Color"]   = convertMode(m_colors["Fill Color"]);
    m_colors["Outline Color"] = convertMode(m_colors["Fill Color"]);
    m_colors["Label Color"]   = convertMode(m_colors["Fill Color"]);
}

void Dropdownbox::draw(sf::RenderWindow& surface) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(surface);
    update(mousePos);

    // BACKGORUND
    m_button.setFillColor(m_colors["Fill Color"]);
    m_button.setOutlineColor(m_colors["Outline Color"]);
    surface.draw(m_button);

    // TEXT
    m_text.setFillColor(m_colors["Label Color"]);
    surface.draw(m_text);

    if(m_isOpen) {
        showMenu(surface);
        for(unsigned int i = 0; i < m_itemTexts.size(); i++) {
            surface.draw(m_itemButtons[i]);
            surface.draw(m_itemTexts[i]);
        }
    }
}

void Dropdownbox::toggleMenu() {
    m_isOpen = !m_isOpen;
}

void Dropdownbox::selectItem(unsigned int index) {
    m_selectedItem = index;
    m_text.setString(m_itemTexts[index].getString());
    m_isOpen = false;
}

void Dropdownbox::showMenu(const sf::RenderWindow& surface) {
    sf::Vector2f pos  = m_button.getPosition();
    sf::Vector2f size = m_button.getSize();

    for(unsigned int i = 0; i < m_itemButtons.size(); i++) {
        float y = pos.y + ((i + 1) * size.y);

        float padding = size.x * 0.1f;

        m_itemButtons[i].setPosition(sf::Vector2f(pos.x + padding/2.0f, y));
        m_itemButtons[i].setSize(sf::Vector2f(size.x - padding, size.y));
        m_itemButtons[i].setFillColor(m_colors["Fill Color"]);
        m_itemButtons[i].setOutlineColor(m_colors["Outline Color"]);
        m_itemButtons[i].setOutlineThickness(m_button.getOutlineThickness());

        m_itemTexts[i].setFillColor(m_colors["Label Color"]);

        m_itemTexts[i].setCharacterSize(std::min(size.x, size.y) / 2.0f);
        const sf::FloatRect bounds = m_itemTexts[i].getLocalBounds();
        const sf::Vector2f labelPos = { pos.x + size.x / 2.0f - bounds.width  / 2.0f - bounds.left, 
                                        y + size.y / 2.0f - bounds.height / 2.0f - bounds.top };
        m_itemTexts[i].setPosition(labelPos);
    }

}