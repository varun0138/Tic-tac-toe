#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <map>

#include "UserInterface.hpp"


class Slider: public UserInterface {
private:
    sf::RectangleShape m_track;
    sf::RectangleShape m_handle;  

    std::map<std::string, sf::Color> m_colors;
    int m_start, m_end, m_current, m_step;

    bool m_handleGrabbed  = false;
    bool m_handleMovement = true;

    sf::Vector2f m_previousHandlePos;

    void moveHandle(const sf::Vector2i& mousesPos);

public:
    Slider(const sf::Vector2f& pos, const sf::Vector2f& size, float thickness, int start, int end, int step, Mode mode);

    int getCurrentValue() const;
    bool isHandleMoved();

    void setMovement(bool move);

    void setMode(Mode mode) override;
    void draw(sf::RenderWindow& surface)override;
};