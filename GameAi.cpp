#include "GameAi.hpp"

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