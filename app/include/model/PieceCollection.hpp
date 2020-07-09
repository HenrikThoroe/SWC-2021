#pragma once

#include <array>

#include "Piece.hpp"

namespace Model {

    class PieceCollection {
        private:
            static const std::array<Piece, 0> allPieces;

        public:
            PieceCollection() = delete;
            PieceCollection(const PieceCollection&) = delete;
            PieceCollection(const PieceCollection*) = delete;

            static const Piece& getPiece(const int& index);
    };

}