#pragma once

#include <vector>
#include <SFML/System/Vector2.hpp>

enum State: unsigned int {
    EMPTY      = 0,
    CROSS      = 1,
    NAUGHT     = 2,
    CROSS_WIN  = 3,
    NAUGHT_WIN = 4
};

struct WinInfo {
    State state;
    std::vector<sf::Vector2u> line;
};


class Board {
private:
    unsigned int m_size;
    std::vector<std::vector<State>> m_board;

public:
    Board(unsigned int size);

    void setState(unsigned int row, unsigned int col, State state);

    bool validCoords(unsigned int row, unsigned int col) const;
    bool checkDraw() const;
    WinInfo checkWin() const;
    State getState(unsigned int row, unsigned int col) const;
};