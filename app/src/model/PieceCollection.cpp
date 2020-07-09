#include "PieceCollection.hpp"

namespace Model {

    const std::array<Piece, 0> PieceCollection::allPieces = {};

    const Piece& PieceCollection::getPiece(const int& index) {
        return allPieces.at(index);
    }   

}