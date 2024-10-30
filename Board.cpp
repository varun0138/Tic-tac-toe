#include "Board.hpp"

Board::Board(unsigned int size)
    : m_size(size), m_board(m_size, std::vector<State>(m_size, EMPTY)) {}

void Board::setState(unsigned int row, unsigned int col, State state) {
    m_board[row][col] = state;
}

bool Board::validCoords(unsigned int row, unsigned int col) const {
    return 0 <= row && row < m_size && 0 <= col && col < m_size;
}

bool Board::checkDraw() const {
    for(unsigned int y = 0; y < m_size; y++) {
        for(unsigned int x = 0; x < m_size; x++) {
            if(m_board[y][x] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

WinInfo Board::checkWin() const {
    // Helper lambda function to check if all elements in a line are the same
    static auto allEqual = [](const std::vector<State>& line) -> State {
        State ref = line[0];
        if (ref == EMPTY) return EMPTY;
        for (State s : line) {
            if (s != ref) return EMPTY;
        }
        return ref;
    };

    std::vector<State> line(m_size);
    std::vector<sf::Vector2u> lineCoords(m_size, sf::Vector2u(0, 0));

    // Check rows
    for (unsigned int y = 0; y < m_size; ++y) {
        for (unsigned int x = 0; x < m_size; ++x) {
            line[x] = m_board[y][x];
            lineCoords[x] = {y, x};
        }
        State winner = allEqual(line);
        if (winner != EMPTY) return {winner, lineCoords};
    }

    // Check columns
    for (unsigned int x = 0; x < m_size; ++x) {
        for (unsigned int y = 0; y < m_size; ++y) {
            line[y] = m_board[y][x];
            lineCoords[y] = {y, x};
        }
        State winner = allEqual(line);
        if (winner != EMPTY) return {winner, lineCoords};
    }

    // Check main diagonal (top-left to bottom-right)
    for (unsigned int i = 0; i < m_size; ++i) {
        line[i] = m_board[i][i];
        lineCoords[i] = {i, i};
    }
    State winner = allEqual(line);
    if (winner != EMPTY) return {winner, lineCoords};

    // Check anti-diagonal (top-right to bottom-left)
    for (unsigned int i = 0; i < m_size; ++i) {
        line[i] = m_board[i][m_size - 1 - i];
        lineCoords[i] = {i, m_size - 1 - i};
    }
    winner = allEqual(line);
    if (winner != EMPTY) return {winner, lineCoords};

    // No winner found
    return {EMPTY, std::vector<sf::Vector2u>()};
}

State Board::getState(unsigned int row, unsigned int col) const {
    return m_board[row][col];
}