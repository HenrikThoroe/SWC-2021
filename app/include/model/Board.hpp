#pragma once

#include <array>
#include <inttypes.h>
#include <iostream>

#include "Move.hpp"
#include "DeployedPiece.hpp"

namespace Model {

    class Board {
        public:
            /// A shorthand for a two dimensional array of the size 20x20 (BoardSize x BoardSize), which stores the color of the field.
            typedef std::array<std::array<PieceColor, 20>, 20> FieldSet;

            /// A shorthand for a two dimensional array of the size 20x20 (BoardSize x BoardSize), which stores one byte per field.
            typedef std::array<std::array<int8_t, 20>, 20> RawFieldSet;

            Board();

            /// Deploys a piece on the current board instance.
            void dropPiece(const DeployedPiece& piece);

            /// Removes a piece from the current board instance.
            void removePiece(const DeployedPiece& piece);

            /// Reads the piece color at the given position.
            const PieceColor& at(const Util::Position& position) const;

            /// Reads the piece color at the given coordinates.
            const PieceColor& at(int x, int y) const;

            friend std::ostream& operator << (std::ostream& os, const Board& board);

        private:
            /// A 20x20 array which stores the piece color for each position of the board.
            FieldSet fields {};

            /// An array which stores four representations of the board. 
            /// Each field of the board is described by an uint8_t value which indicates the number of possible attach points.
            /// If the value is 0 no piece can be attached to this position.
            /// @note 'dropPositions' should be indexed with instances of 'PieceColor'.
            std::array<RawFieldSet, 4> dropPositions {};
    };

}