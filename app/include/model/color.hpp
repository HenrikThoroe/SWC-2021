#pragma once

#include <inttypes.h>
#include <iostream>

namespace Model {

    /** 
     * A position on the game board can be occupied by any color (red, green, blue, yellow).
     * If the position is unoccupied it could be obstructed (OBSTRUCTED) or empty (NONE).
     * 
     * @brief An enumeration indicating the state of a single position on the game board. 
     * @note The enum maps to uint8_t
     */ 
    enum class PieceColor: uint8_t {
        NONE = 0, 
        RED = 1, 
        BLUE = 2, 
        GREEN = 3, 
        YELLOW = 4, 
        OBSTRUCTED = 5
    };

    std::ostream& operator << (std::ostream& os, const PieceColor& color);

    /**
     * The colorful representation of a player. Each player has one color assigned. Possible colors are red and blue.
     * 
     * @note The enum maps to uint8_t
     */ 
    enum class PlayerColor: uint8_t {
        BLUE = 0,
        RED = 1
    };

    std::ostream& operator << (std::ostream& os, const PlayerColor& color);

}