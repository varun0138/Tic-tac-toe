#include "GameAi.hpp"

#include <vector>

GameAi::GameAi() {}

sf::Vector2u GameAi::randomMove(const Board& board, unsigned int size) {
    std::vector<sf::Vector2u> moves;

    for(unsigned int y = 0; y < size; y++) {
        for(unsigned int x = 0; x < size; x++) {
            if(board.getState(x, y) == EMPTY) {
                moves.push_back({ x, y });
            }
        }
    }

    unsigned int index = m_random.randint(0, moves.size());
    return moves[index];
}

sf::Vector2u GameAi::greedyMove(const Board& board, unsigned int size, State state) {
    Board temp = board;
    State opponent = (state == CROSS) ? NAUGHT: CROSS;

    // Winning move
    for(unsigned int y = 0; y < size; y++) {
        for(unsigned int x = 0; x < size; x++) {
            if(temp.getState(x, y) == EMPTY) {
                temp.setState(x, y, state);
                if(temp.checkWin().state == state) {
                    return {x, y};
                }
                temp.setState(x, y, EMPTY);
            }
        }
    }

    // Blocking move
    for(unsigned int y = 0; y < size; y++) {
        for(unsigned int x = 0; x < size; x++) {
            if(temp.getState(x, y) == EMPTY) {
                temp.setState(x, y, opponent);
                if(temp.checkWin().state == opponent) {
                    return {x, y};
                }
                temp.setState(x, y, EMPTY);
            }
        }
    }

    // Follow a line
    std::vector<State> line(size);
    std::vector<sf::Vector2u> lineCoords;

    for (unsigned int y = 0; y < size; ++y) {
        // Check rows
        lineCoords.clear();
        bool lineClear = true;
        for (unsigned int x = 0; x < size; ++x) {
            line[x] = board.getState(y, x);
            if(line[x] == opponent) {
                lineClear = false;
                break;
            }
            if(line[x] == EMPTY) {
                lineCoords.push_back({y, x});
            }
        }
        if(lineClear && lineCoords.size() > 0) {
            return lineCoords[0];
        }

        // check columns
        lineCoords.clear();
        lineClear = true;
        for (unsigned int x = 0; x < size; ++x) {
            line[x] = board.getState(x, y);
            if(line[x] == opponent) {
                lineClear = false;
                break;
            }
            if(line[x] == EMPTY) {
                lineCoords.push_back({x, y});
            }
        }
        if(lineClear && lineCoords.size() > 0) {
            return lineCoords[0];
        }
    }

    // Check main diagonal (top-left to bottom-right)
    lineCoords.clear();
    bool lineClear = true;
    for (unsigned int i = 0; i < size; ++i) {
        line[i] = board.getState(i, i);
        if(line[i] == opponent) {
            lineClear = false;
            break;
        }
        if(line[i] == EMPTY) {
            lineCoords.push_back({i, i});
        }
    }
    if(lineClear && lineCoords.size() > 0) {
        return lineCoords[0];
    }


    // Check anti-diagonal (top-right to bottom-left) 
    lineClear = true;
    lineCoords.clear();
    for (unsigned int i = 0; i < size; ++i) {
        line[i] = board.getState(i, size - 1 - i);
        if(line[i] == opponent) {
            lineClear = false;
            break;
        }
        if(line[i] == EMPTY) {
            lineCoords.push_back({i, size - 1 - i});
        }
    }
    if(lineClear && lineCoords.size() > 0) {
        return lineCoords[0];
    }

    // Center
    if(board.getState(size / 2, size / 2) == EMPTY) {
        return {size / 2, size / 2};
    }

    // Corner
    if(board.getState(0, 0) == EMPTY) return {0, 0};
    if(board.getState(0, size - 1) == EMPTY) return {0, size - 1};
    if(board.getState(size - 1, 0) == EMPTY) return {size - 1, 0};
    if(board.getState(size - 1, size - 1) == EMPTY) return {size - 1, size - 1};

    sf::Vector2u move = randomMove(board, size);
    return move;
}