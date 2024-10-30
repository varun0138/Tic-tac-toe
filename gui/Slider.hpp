#pragma once

#include <SFML/Graphics.hpp>

#include "UserInterface.hpp"


class Slider: public UserInterface {
private:
    sf::RectangleShape m_track;
    sf::RectangleShape m_handle;

    sf::Vector2f m_trackPos = { 10.0f, 10.0f };
    sf::Vector2f m_trackSize = { 120.0f, 50.0f };

    sf::Vector2f m_handlePos = { 10.0f, 10.0f };
    sf::Vector2f m_handleSize = { 120.0f, 50.0f };  

    sf::Color m_colors[4] = { {220, 220, 220, 255}, {146, 134, 148, 255}, {57, 62, 67, 255}};

    sf::Color m_fillColor    = m_colors[0];
    sf::Color m_clickColor   = m_colors[1];
    sf::Color m_outlineColor = m_colors[2];

    float m_thickness = 2.0f;
    int m_start = 1;
    int m_end = 10;
    int m_current = m_start;
    int m_increment = 1; // New increment variable
    bool m_handleGrabbed = false;  // To track if the handle is grabbed

    sf::Vector2f m_previousHandlePos = { 10.0f, 10.0f };

    void moveHandle(const sf::Vector2f& mousePos);

public:
    Slider(const sf::Vector2f& pos, const sf::Vector2f& size, Mode mode=DARK);

    void setRange(int start, int end, int increment = 1);
    void setMode(Mode mode);

    int getCurrentValue() const;
    bool isMoved();

    void draw(sf::RenderWindow& surface);
};