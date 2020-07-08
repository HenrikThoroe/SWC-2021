#pragma once

#include <inttypes.h>

#include "color.hpp"
#include "Rotation.hpp"
#include "Position.hpp"
#include "Vector2D.hpp"

namespace Model {

    /// Move stores information to perform a move on the game board.
    struct Move {
        /// The id of the piece which is involved in the current move.
        uint8_t pieceId;

        /// The color of the set piece.
        PieceColor color;

        /// The rotation of the piece.
        Rotation rotation;

        /// The position on the board where the piece should be deployed.
        Util::Position positionOnBoard;

        /**
         * Each piece is described by a bunch of vectors where each vector points to a position on the piece shape.
         * If the piece's attach point for the current move is any but the default origin, which identifies the piece's shape,
         * another vector is required which points from the attach point to the piece's origin.
         * 
         * @brief A vector pointing to the origin of the piece.
         */
        Util::Vector2D vectorToOrigin;
    };

}