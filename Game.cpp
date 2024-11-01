#include "Game.hpp"

#include <iostream>

Game::Game() {
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "", sf::Style::Close | sf::Style::Titlebar);
    m_assets.loadFromFile("./assets.txt");

    m_labels["Current Player"] = std::make_unique<Label>(m_assets.getFont("Hack"), sf::Vector2f(700, 400), 32, "", DARK);
    m_labels["Final Result"] = std::make_unique<Label>(m_assets.getFont("Hack"), sf::Vector2f(700, 450), 32, "", DARK);
    m_labels["Game Size"] = std::make_unique<Label>(m_assets.getFont("Hack"), sf::Vector2f(700, 50), 32, "", DARK);

    m_labels["Player X"] = std::make_unique<Label>(m_assets.getFont("Hack"), sf::Vector2f(700, 200), 30, "Player:X", DARK);
    m_labels["Player O"] = std::make_unique<Label>(m_assets.getFont("Hack"), sf::Vector2f(700, 300), 30, "Player:O", DARK);

    init();

    m_sizeSlider = std::make_unique<Slider>(sf::Vector2f(700, 100), sf::Vector2f(350, 25), 3.0f, 3, 17, 2, DARK);

    m_players = { "Human", "Random" };

    m_crossPlayerMenu = std::make_unique<Dropdownbox>(m_assets.getFont("Hack"), sf::Vector2f(870, 190), sf::Vector2f(210, 60), 1.0f, "None", m_players, LIGHT);
    m_naughtPlayerMenu = std::make_unique<Dropdownbox>(m_assets.getFont("Hack"), sf::Vector2f(870, 290), sf::Vector2f(210, 60), 1.0f, "None", m_players, LIGHT);
}

void Game::run() {
    while(m_window.isOpen()) {
        handleInput();
        update();
        render();
    }
}

void Game::init() {
    m_tileSize = m_boardSize / m_size;
    m_gap = m_tileSize * 0.05;

    m_board = std::make_unique<Board>(m_size);
    m_currentPlayer = CROSS;
    m_mouseClicked = false;
    m_gameEnded = false;

    m_labels["Current Player"]->caption = std::string("Current Player: ") + ((m_currentPlayer == CROSS) ? "X" : "O");
    m_labels["Final Result"]->caption   = "Results: None";
    m_labels["Game Size"]->caption      = "SIZE: " + std::to_string(m_size);
}

void Game::handleInput() {
    sf::Event event;
    while(m_window.pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed:
                m_window.close();
                break;

            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left) {
                    m_mouseClicked = true;
                }
                break;

            default:
                break;
        }
    }
}

void Game::update() {
    // USER INTERFACE
    if(m_sizeSlider->isHandleMoved()) {
        m_size = m_sizeSlider->getCurrentValue();
        init();
        m_labels["Game Size"]->caption = "SIZE: " + std::to_string(m_size);
    }

    std::string player = "";
    if(m_currentPlayer == CROSS) {
        player = m_crossPlayerMenu->getSelectedItem();
    }
    else if(m_currentPlayer == NAUGHT) {
        player = m_naughtPlayerMenu->getSelectedItem();
    }
    
    // GAME LOGIC
    if(m_gameEnded) { return; }

    sf::Vector2u move = { m_size, m_size };
    if(player == "Human") {
        move = humanMove();
    }
    else if(player == "Random") {
        move = gameAi.randomMove(*m_board, m_size);
    }

    unsigned int row = move.x;
    unsigned int col = move.y;

    if(m_board->validCoords(row, col) && m_board->getState(row, col) == EMPTY) {
        m_board->setState(row, col, m_currentPlayer);

        // CHECK WIN
        const WinInfo won = m_board->checkWin();
        switch(won.state) {
            case CROSS:
                m_labels["Final Result"]->caption = "Results: Cross Wins";
                for(unsigned int i = 0; i < won.line.size(); i++) {
                    m_board->setState(won.line[i].x, won.line[i].y, CROSS_WIN);
                }
                m_gameEnded = true;
                break;

            case NAUGHT:
                m_labels["Final Result"]->caption = "Results: Naught Wins";
                for(unsigned int i = 0; i < won.line.size(); i++) {
                    m_board->setState(won.line[i].x, won.line[i].y, NAUGHT_WIN);
                }
                m_gameEnded = true;
                break;

            default:
                m_labels["Final Result"]->caption = "Results: None";
                break;
        }

        // CHECK DRAW
        if(m_board->checkDraw()) {
            m_labels["Final Result"]->caption = "Results: Game Draw";
            m_gameEnded = true;
        }

        // CHANGE TURNS
        changeTurns();
    }
}

void Game::changeTurns() {
    m_currentPlayer = (m_currentPlayer == CROSS) ? NAUGHT : CROSS;
    m_labels["Current Player"]->caption = std::string("Current Player: ") + ((m_currentPlayer == CROSS) ? "X" : "O");
}

sf::Vector2u Game::humanMove() {
    if(m_mouseClicked) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window) - m_boardPos;
        unsigned int row = mousePos.y / m_tileSize;
        unsigned int col = mousePos.x / m_tileSize;

        m_mouseClicked = false;
        return { row, col };
    }
    return { m_size, m_size };
}


void Game::renderSprite(const std::string& name, unsigned int x, unsigned int y) {
    sf::Sprite& sprite = m_assets.getSprite(name);
    sf::Vector2u size = sprite.getTexture()->getSize();
    sf::Vector2f scale = { (m_tileSize - m_gap) / size.x, (m_tileSize - m_gap) / size.y };

    sprite.setScale(scale);
    sprite.setPosition(sf::Vector2f(y * m_tileSize + m_boardPos.x, x * m_tileSize + m_boardPos.y));
    m_window.draw(sprite);
}

void Game::render() {
    m_window.clear(m_backgroundColor);

    for(unsigned int y = 0; y < m_size; y++) {
        for(unsigned int x = 0; x < m_size; x++) {
            renderSprite("Tile", x, y);

            switch(m_board->getState(x, y)) {
                case CROSS:      renderSprite("Cross", x, y);     break;
                case NAUGHT:     renderSprite("Naught", x, y);    break;
                case CROSS_WIN:  renderSprite("CrossWin", x, y);  break;
                case NAUGHT_WIN: renderSprite("NaughtWin", x, y); break;
                default:                                          break;
            }
        }
    }

    for(const auto&[key, value]: m_labels) {
        m_labels[key]->draw(m_window);
    }

    m_sizeSlider->draw(m_window);

    m_naughtPlayerMenu->draw(m_window);
    m_crossPlayerMenu->draw(m_window);

    m_window.display();
}