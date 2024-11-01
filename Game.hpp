#pragma once 

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <map>

#include "Board.hpp"
#include "AssetManager.hpp"
#include "GameAi.hpp"
#include "gui/Label.hpp"
#include "gui/Slider.hpp"
#include "gui/Dropdownbox.hpp"

class Game {
private:
    sf::RenderWindow m_window;
    AssetManager m_assets;
    GameAi gameAi;

    const sf::Color m_backgroundColor = { 211, 224, 215, 255 };
    const sf::Vector2i m_boardPos = { 35, 10 };

    unsigned int m_size = 3;

    const float m_windowWidth = 1100;
    const float m_windowHeight = 650;

    const float m_boardSize = 630;

    float m_tileSize;
    float m_gap;

    std::unique_ptr<Board> m_board;
    State m_currentPlayer;
    bool m_mouseClicked;
    bool m_gameEnded;

    std::map<std::string, std::unique_ptr<Label>> m_labels;

    std::unique_ptr<Slider> m_sizeSlider;

    std::vector<std::string> m_players;

    std::unique_ptr<Dropdownbox> m_crossPlayerMenu;
    std::unique_ptr<Dropdownbox> m_naughtPlayerMenu;

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