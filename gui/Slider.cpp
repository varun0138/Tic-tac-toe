#include "Slider.hpp"

static int mapValue(int value, float inMin, float inMax, float outMin, float outMax) {
    if (inMax == inMin) return outMin;
    return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}


Slider::Slider(const sf::Vector2f& pos, const sf::Vector2f& size)
    : m_trackPos(pos), m_trackSize(size) {

    m_handlePos  = { pos.x, pos.y};
    m_handleSize = { size.x / 5.0f, size.y }; 
}

void Slider::setRange(int start, int end, int increment) {
    m_start = start;
    m_end = end;
    m_increment = increment > 0 ? increment : 1; // Ensure increment is positive
    m_current = start;
}

void Slider::setMode(Mode mode) {
    m_fillColor    = convertMode(m_colors[0], mode);
    m_clickColor   = convertMode(m_colors[1], mode);
    m_outlineColor = convertMode(m_colors[2], mode);
}

int Slider::getCurrentValue() const {
    return m_current;
}

void Slider::draw(sf::RenderWindow& surface) {
    sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(surface);
    moveHandle(mousePos);

    m_track.setPosition(m_trackPos);
    m_track.setSize(m_trackSize);
    m_track.setFillColor(m_fillColor);
    m_track.setOutlineColor(m_outlineColor);
    m_track.setOutlineThickness(m_thickness);

    m_handle.setPosition(m_handlePos);
    m_handle.setSize(m_handleSize);
    m_handle.setFillColor(m_outlineColor);
    m_handle.setOutlineColor(m_outlineColor);
    m_handle.setOutlineThickness(m_thickness);

    // Get the current value using mapValue
    int value = mapValue(m_handlePos.x, m_trackPos.x, m_trackPos.x + m_trackSize.x - m_handleSize.x, m_start, m_end);

    // Snap to the nearest increment
    m_current = m_start + ((value - m_start + m_increment / 2) / m_increment) * m_increment;

    surface.draw(m_track);
    surface.draw(m_handle);
}


bool Slider::isMoved() {
    bool moved = (m_handlePos != m_previousHandlePos);
    m_previousHandlePos = m_handlePos;
    return moved;
}


void Slider::moveHandle(const sf::Vector2f& mousePos) {
    // Check if the mouse button is pressed
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        // If handle is not grabbed yet, check if the mouse clicked on the handle
        if (!m_handleGrabbed) {
            if (mousePos.x >= m_handlePos.x && mousePos.x <= m_handlePos.x + m_handleSize.x &&
                mousePos.y >= m_handlePos.y && mousePos.y <= m_handlePos.y + m_handleSize.y) {
                m_handleGrabbed = true;  // The mouse clicked the handle
            }
        }

        // If the handle is grabbed, move it with the mouse
        if (m_handleGrabbed) {
            m_handlePos.x = mousePos.x - m_handleSize.x / 2.0f;  // Center handle on mouse
            // Clamp the handle position within the track bounds
            if (m_handlePos.x < m_trackPos.x) m_handlePos.x = m_trackPos.x;
            if (m_handlePos.x > m_trackPos.x + m_trackSize.x - m_handleSize.x) 
                m_handlePos.x = m_trackPos.x + m_trackSize.x - m_handleSize.x;
        }
    } else {
        // Release the handle when the mouse button is released
        m_handleGrabbed = false;
    }
}
