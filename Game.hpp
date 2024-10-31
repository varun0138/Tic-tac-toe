#pragma once 

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <stack>

#include "Board.hpp"
#include "AssetManager.hpp"
#include "gui/Label.hpp"
#include "gui/Button.hpp"
#include "gui/Slider.hpp"

class Game {
private:
    sf::RenderWindow m_window;
    AssetManager m_assets;

    const sf::Color m_backgroundColor = { 211, 224, 215, 255 };
    const sf::Vector2i m_boardPos = { 50, 20 };

    unsigned int m_size = 3;

    const float m_windowWidth = 1100;
    const float m_windowHeight = 700;

    const float m_boardSize = 630;

    float m_tileSize;
    float m_gap;

    std::stack<sf::Vector2u> m_moves;
    std::unique_ptr<Board> m_board;
    State m_currentPlayer;
    bool m_mouseClicked;
    bool m_gameEnded;

    std::string m_playerText;
    std::string m_resultText;
    std::string m_sizeText;

    std::unique_ptr<Label> m_playerLabel;
    std::unique_ptr<Label> m_resultLabel;
    std::unique_ptr<Label> m_sizeLabel;

    std::vector<std::unique_ptr<Button>> m_buttons;

    std::unique_ptr<Slider> m_sizeSlider;

    void init();
    void renderSprite(const std::string& name, unsigned int x, unsigned int y);
    void changeTurns();
    sf::Vector2u humanMove();

    void handleInput();
    void update();
    void render();

public:
    Game();
    void run();  
};