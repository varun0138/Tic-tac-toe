#include "Game.hpp"

#include <iostream>

Game::Game() {
    m_window.create(sf::VideoMode(m_windowWidth, m_windowHeight), "", sf::Style::Close | sf::Style::Titlebar);
    m_assets.loadFromFile("./assets.txt");

    init();

    m_playerLabel = std::make_unique<Label>(m_assets.getFont("Hack"), sf::Vector2f(700, 400), 32, m_playerText, DARK);
    m_resultLabel = std::make_unique<Label>(m_assets.getFont("Hack"), sf::Vector2f(700, 450), 32, m_resultText, DARK);
    m_sizeLabel = std::make_unique<Label>(m_assets.getFont("Hack"), sf::Vector2f(700, 250), 32, m_resultText, DARK);

    m_buttons.push_back(std::make_unique<Button>(m_assets.getFont("Hack"), sf::Vector2f(700, 50), sf::Vector2f(160, 80), 2.0f, "RESET", LIGHT));
    m_buttons.push_back(std::make_unique<Button>(m_assets.getFont("Hack"), sf::Vector2f(900, 50), sf::Vector2f(160, 80), 2.0f, "UNDO", LIGHT));
    m_buttons.push_back(std::make_unique<Button>(m_assets.getFont("Hack"), sf::Vector2f(940, 600), sf::Vector2f(150, 80), 2.0f, "EXIT", LIGHT));

    m_sizeSlider = std::make_unique<Slider>(sf::Vector2f(700, 300), sf::Vector2f(350, 25), 3.0f, 3, 17, 2, DARK);
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

    m_moves = std::stack<sf::Vector2u>();
    m_board = std::make_unique<Board>(m_size);
    m_currentPlayer = CROSS;
    m_mouseClicked = false;
    m_gameEnded = false;

    m_playerText = std::string("Current Player: ") + ((m_currentPlayer == CROSS) ? "X" : "O");
    m_resultText = "Results: None";
    m_sizeText   = "SIZE: " + std::to_string(m_size);
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
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(m_window);
        std::string clickedButton = "";
        for(unsigned int i = 0; i < m_buttons.size(); i++) {
            if(m_buttons[i]->buttonClicked(mousePos)) {
                clickedButton = m_buttons[i]->getLabel();
                break;
            }
        }

        if(clickedButton == "RESET") {
            init();
        }
        else if(clickedButton == "UNDO" && !m_moves.empty() && !m_gameEnded) {
            sf::Vector2u move = m_moves.top();
            m_moves.pop();
            m_board->setState(move.x, move.y, EMPTY);
            changeTurns();
        }
        else if(clickedButton == "EXIT") {
            m_window.close();
        }

        if(m_sizeSlider->isHandleMoved()) {
            m_size = m_sizeSlider->getCurrentValue();
            init();
            m_sizeText = "SIZE: " + std::to_string(m_size);
        }

        m_playerLabel->setLabel(m_playerText);
        m_resultLabel->setLabel(m_resultText);
        m_sizeLabel->setLabel(m_sizeText);
    }

    if(m_gameEnded) {
        return;
    }

    sf::Vector2u move = humanMove();
    unsigned int row = move.x;
    unsigned int col = move.y;

    if(m_board->validCoords(row, col) && m_board->getState(row, col) == EMPTY) {
        m_board->setState(row, col, m_currentPlayer);
        m_moves.push(move);

        // CHECK WIN
        const WinInfo won = m_board->checkWin();
        switch(won.state) {
            case CROSS:
                m_resultText = "Results: Cross Wins";
                for(unsigned int i = 0; i < won.line.size(); i++) {
                    m_board->setState(won.line[i].x, won.line[i].y, CROSS_WIN);
                }
                m_gameEnded = true;
                break;

            case NAUGHT:
                m_resultText = "Results: Naught Wins";
                for(unsigned int i = 0; i < won.line.size(); i++) {
                    m_board->setState(won.line[i].x, won.line[i].y, NAUGHT_WIN);
                }
                m_gameEnded = true;
                break;

            default:
                m_resultText = "Results: None";
                break;
        }

        // CHECK DRAW
        if(m_board->checkDraw()) {
            m_resultText = "Results: Game Draw";
            m_gameEnded = true;
        }

        // CHANGE TURNS
        changeTurns();
    }
}

void Game::changeTurns() {
    m_currentPlayer = (m_currentPlayer == CROSS) ? NAUGHT : CROSS;
    m_playerText = std::string("Current Player: ") + ((m_currentPlayer == CROSS) ? "X" : "O");
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

    m_playerLabel->draw(m_window);
    m_resultLabel->draw(m_window);
    m_sizeLabel->draw(m_window);

    for(unsigned int i = 0; i < m_buttons.size(); i++) {
        m_buttons[i]->draw(m_window);
    }

    m_sizeSlider->draw(m_window);

    m_window.display();
}