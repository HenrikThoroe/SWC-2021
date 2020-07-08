#include "Board.hpp"
#include "Piece.hpp"
#include <vector>

namespace Model {

    Board::Board() {}

    void Board::perform(const Move& move) {
        using Util::Vector2D;
        using Util::Position;

        const Position origin = move.positionOnBoard.move(move.vectorToOrigin);
        std::vector<Position> positionsOfPiece;
        const Piece::Shape shape = std::get<0>(Piece::allPieces.at(move.pieceId).rotations.at(uint8_t(move.rotation))); 

        for (auto path : shape) {
            positionsOfPiece.push_back(origin.move(path));
        }

        for (auto pos : positionsOfPiece) {
            fields[pos.x][pos.y] = uint8_t(move.color);
        }
    }

    bool Board::canPerform(const Move& move) const {
        // ToDo: Implement 
        return false;
    }

}