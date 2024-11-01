#pragma once

#include <SFML/System/Vector2.hpp>

#include "Random.hpp"
#include "Board.hpp"

class GameAi {
private:
    Random m_random;

public:
    GameAi();

    sf::Vector2u randomMove(const Board& board, unsigned int size);
    sf::Vector2u greedyMove(const Board& board, unsigned int size, State state);
};