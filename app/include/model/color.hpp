#pragma once

#include <inttypes.h>

namespace Model {

    /** 
     * A position on the game board can be occupied by any color (red, green, blue, yellow).
     * If the position is unoccupied it could be obstructed (OBSTRUCTED) or empty (NONE).
     * 
     * @brief An enumeration indicating the state of a single position on the game board. 
     * @note The enum maps to uint8_t
     */ 
    enum class PieceColor: uint8_t {
        RED, BLUE, GREEN, YELLOW, NONE, OBSTRUCTED
    };

    /**
     * The colorful representation of a player. Each player has one color assigned. Possible colors are red and blue.
     * 
     * @note The enum maps to uint8_t
     */ 
    enum class PlayerColor: uint8_t {
        RED, BLUE
    };

}