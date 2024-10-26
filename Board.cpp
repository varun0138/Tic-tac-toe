#include "Board.hpp"

Board::Board(unsigned int size) {
    setUp(size);
}

void Board::setUp(unsigned int size) {
    m_size = size;
    m_board = std::vector<std::vector<State>>(m_size, std::vector<State>(m_size, EMPTY));
}

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

State Board::checkWin() const {
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

    // Check rows
    for (unsigned int y = 0; y < m_size; ++y) {
        for (unsigned int x = 0; x < m_size; ++x) line[x] = m_board[y][x];
        State winner = allEqual(line);
        if (winner != EMPTY) return winner;
    }

    // Check columns
    for (unsigned int x = 0; x < m_size; ++x) {
        for (unsigned int y = 0; y < m_size; ++y) line[y] = m_board[y][x];
        State winner = allEqual(line);
        if (winner != EMPTY) return winner;
    }

    // Check main diagonal (top-left to bottom-right)
    for (unsigned int i = 0; i < m_size; ++i) line[i] = m_board[i][i];
    State winner = allEqual(line);
    if (winner != EMPTY) return winner;

    // Check anti-diagonal (top-right to bottom-left)
    for (unsigned int i = 0; i < m_size; ++i) line[i] = m_board[i][m_size - 1 - i];
    winner = allEqual(line);
    if (winner != EMPTY) return winner;

    // No winner found
    return EMPTY;
}


State Board::getState(unsigned int row, unsigned int col) const {
    return m_board[row][col];
}

unsigned int Board::getSize() const {
    return m_size;
}

// DEBUGGING
#include <iostream>
void Board::DEBUG() {

    // for(unsigned int y = 0; y < m_size; y++) {
    //     for(unsigned int x = 0; x < m_size; x++) {
    //         std::cout << m_board[y][x] << " ";
    //     }
    //     std::cout << std::endl;
    // }
    // std::cout << std::endl;

    for(unsigned int y = 0; y < m_size; y++) {
        for(unsigned int x = 0; x < m_size; x++) {
            if(m_board[y][x] == EMPTY) {
                std::cout << '_' << " ";
            }
            else if(m_board[y][x] == CROSS) {
                std::cout << 'X' << " ";
            }
            else if(m_board[y][x] == NAUGHT) {
                std::cout << 'O' << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

}