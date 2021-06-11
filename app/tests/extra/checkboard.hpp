#pragma once

#include <vector>
#include <array>

#include "Board.hpp"

namespace TestExtra {

    /// Type that holds positions on the board
    typedef std::array<int, 2> BoardPosition;
    typedef std::vector<BoardPosition> BoardPositions;

    /**
     * @brief Check if colors occupy specific positions on the board (ONLY FOR TESTS)
     * 
     * @param board The board to check
     * @param blue Positions that should be occupied by blue
     * @param red Positions that should be occupied by red
     * @param yellow Positions that should be occupied by yellow
     * @param green Positions that should be occupied by green
     * 
     * @returns BoardPositions that did not have the right color
     */
    BoardPositions checkBoard(const Model::Board& board, const BoardPositions& blue, const BoardPositions& red, const BoardPositions& yellow, const BoardPositions& green);

}
