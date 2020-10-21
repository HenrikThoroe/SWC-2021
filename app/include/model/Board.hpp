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
            Board(Board* other) = delete;
            Board(Board& other) = delete;

            /// Deploys a piece on the current board instance.
            void dropPiece(const DeployedPiece& piece);

            /// Removes a piece from the current board instance.
            void removePiece(const DeployedPiece& piece);

            /// Reads the piece color at the given position.
            const PieceColor& at(const Util::Position& position) const;

            /// Reads the piece color at the given coordinates.
            const PieceColor& at(int x, int y) const;

            /// Calculates the available drop positions for the specified color.
            std::vector<Util::Position> getDropPositions(const PieceColor& color) const;

            /// Checks if a piece of the passed color can be droped at the given position.
            bool canDrop(const PieceColor& color, const Util::Position& position) const;

            /// Checks if a piece of the passed color can be droped at the given coordinates.
            bool canDrop(const PieceColor& color, int x, int y) const;

            /// Forces the specified position to be a drop zone for the passed color.
            void makeDropPosition(const Util::Position& position, const PieceColor& color);

            friend std::ostream& operator << (std::ostream& os, const Board& board);

            const PieceColor& operator [] (const Util::Position& position) const;

        private:
            /// A 20x20 array which stores the piece color for each position of the board.
            FieldSet fields {};

            /// An array which stores four representations of the board. 
            /// Each field of the board is described by an uint8_t value which indicates the number of possible attach points.
            /// If the value is 0 no piece can be attached to this position.
            /// @note 'dropPositions' should be indexed with instances of 'PieceColor' - 1.
            std::array<RawFieldSet, 4> dropPositions {};
    };

}
