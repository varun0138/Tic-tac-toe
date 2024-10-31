#include <SFML/Window/Mouse.hpp>
#include <cmath>

#include "Slider.hpp"

static inline int mapValue(int value, float inMin, float inMax, float outMin, float outMax) {
    if (inMax == inMin) return outMin;
    return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
}


Slider::Slider(const sf::Vector2f& pos, const sf::Vector2f& size, float thickness, int start, int end, int step, Mode mode) {
    m_track.setPosition(pos);
    m_track.setSize(size);
    m_track.setOutlineThickness(thickness);

    m_handle.setPosition(pos);
    m_handle.setSize(sf::Vector2f(size.x / 5.0f, size.y));
    m_handle.setOutlineThickness(thickness);

    m_colors["Fill Color"]    = {220, 220, 220, 255};
    m_colors["Click Color"]   = {146, 134, 148, 255};
    m_colors["Outline Color"] = {57,  62,  67,  255};

    if(mode == LIGHT) {
        setMode(mode);
    }

    m_start = start;
    m_end = end;
    m_step = step > 0 ? step : 1;
    m_current = start;
}

void Slider::setMode(Mode mode) {
    m_colors["Fill Color"]    = convertMode(m_colors["Fill Color"]);
    m_colors["Click Color"]   = convertMode(m_colors["Fill Color"]);
    m_colors["Outline Color"] = convertMode(m_colors["Fill Color"]);
}

int Slider::getCurrentValue() const {
    return m_current;
}

bool Slider::isHandleMoved() {
    sf::Vector2f handlePos = m_handle.getPosition();
    bool moved = (handlePos != m_previousHandlePos);
    m_previousHandlePos = handlePos;
    return moved;
}

void Slider::setMovement(bool move) {
    m_handleMovement = move;
}

void Slider::draw(sf::RenderWindow& surface) {
    const sf::Vector2i mousePos = sf::Mouse::getPosition(surface);
    moveHandle(mousePos);

    // TRACK
    m_track.setFillColor(m_colors["Fill Color"]);
    m_track.setOutlineColor(m_colors["Outline Color"]);
    surface.draw(m_track);

    // HANDLE
    m_handle.setFillColor(m_colors["Outline Color"]);
    m_handle.setOutlineColor(m_colors["Outline Color"]);
    surface.draw(m_handle);
}

void Slider::moveHandle(const sf::Vector2i& mousesPos) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_handleMovement) {
        if(!m_handleGrabbed) {
            if(m_handle.getGlobalBounds().contains((sf::Vector2f)mousesPos)) {
                m_handleGrabbed = true;
            }
        }

        if(m_handleGrabbed) {
            sf::Vector2f trackPos = m_track.getPosition();
            sf::Vector2f trackSize = m_track.getSize();
            sf::Vector2f handlePos = m_handle.getPosition();
            sf::Vector2f handleSize = m_handle.getSize();

            handlePos.x = mousesPos.x - handleSize.x / 2.0f;
            if (handlePos.x < trackPos.x) {
                handlePos.x = trackPos.x;
            }
            if (handlePos.x > trackPos.x + trackSize.x - handleSize.x) {
                handlePos.x = trackPos.x + trackSize.x - handleSize.x;
            } 
            
            m_handle.setPosition(handlePos);

            int value = mapValue(handlePos.x, trackPos.x, trackPos.x + trackSize.x - handleSize.x, m_start, m_end);
            m_current = std::floor(m_start + ((value - m_start + m_step / 2) / m_step) * m_step);
        }
    }
    else {
        m_handleGrabbed = false;
    }    
}