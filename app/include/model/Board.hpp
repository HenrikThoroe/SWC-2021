#pragma once

#include <array>
#include <inttypes.h>

#include "Move.hpp"
#include "DeployedPiece.hpp"

namespace Model {

    class Board {
        public:
            /// A shorthand for a two dimensional array of the size 20x20 (BoardSize x BoardSize), which stores one byte per field.
            typedef std::array<std::array<uint8_t, 20>, 20> FieldSet;

            FieldSet fields;

            Board();

            /// Deploys a piece on the current board instance.
            void dropPiece(const DeployedPiece& piece);

        private:
            /// An array which stores four representations of the board. 
            /// Each field of the board is described by an uint8_t value which indicates the number of possible attach points.
            /// If the value is 0 no piece can be attached to this position.
            /// @note 'dropPositions' should be indexed with instances of 'PieceColor'.
            std::array<FieldSet, 4> dropPositions;
    };

}