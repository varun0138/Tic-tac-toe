#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum Mode { LIGHT, DARK };

inline sf::Color convertMode(const sf::Color& color) { 
    return { sf::Uint8(255 - color.r),sf::Uint8(255 - color.g), sf::Uint8(255 - color.b), color.a };
}

class UserInterface {
public:
    virtual void setMode(Mode mode) = 0;
    virtual void draw(sf::RenderWindow& surface) = 0;
};