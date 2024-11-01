#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>

#include "UserInterface.hpp"

class Dropdownbox: public UserInterface {
private:
    sf::RectangleShape m_button;
    sf::Text m_text;

    std::vector<sf::RectangleShape> m_itemButtons;
    std::vector<sf::Text> m_itemTexts;

    std::map<std::string, sf::Color> m_colors;

    int m_selectedItem = -1;
    bool m_isOpen = false;
    bool m_openUpwards = false;
    bool m_mousePressed = false;

    void toggleMenu();
    void selectItem(unsigned int index);
    void showMenu(const sf::RenderWindow& surface);
    void update(const sf::Vector2f& mousePos);

public:
    Dropdownbox(const sf::Font& font, const sf::Vector2f& pos, const sf::Vector2f& size, float thickness, const std::string& label, const std::vector<std::string>& items, Mode mode);

    std::string getSelectedItem() const;

    void setMode(Mode mode) override;
    void draw(sf::RenderWindow& surface) override;
};