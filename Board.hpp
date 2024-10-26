#pragma once

#include <vector>

enum State: unsigned int {
    EMPTY  = 0,
    CROSS  = 1,
    NAUGHT = 2
};

enum Alignment: unsigned int {
    NONE, ROW, COLUMN, MAIN_DIAGONAL, ANTI_DIAGONAL
};

struct Outcome {
    State winner;
    Alignment alignment;
    int index;
};


class Board {
private:
    std::vector<std::vector<State>> m_board;
    unsigned int m_size;

public:
    Board(unsigned int size);

    void setUp(unsigned int size);
    void setState(unsigned int row, unsigned int col, State state);

    bool validCoords(unsigned int row, unsigned int col) const;
    bool checkDraw() const;
    State checkWin() const;
    State getState(unsigned int row, unsigned int col) const;
    unsigned int getSize() const;

    // DEBUGGING
    void DEBUG();
};

