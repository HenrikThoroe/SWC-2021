#include "DeployedPiece.hpp"

namespace Model {

    DeployedPiece::DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation) : pieceId(id), origin(origin), rotation(rotation) {}

    DeployedPiece::DeployedPiece(const DeployedPiece& other) : pieceId(other.pieceId), origin(other.origin), rotation(other.rotation) {}

    DeployedPiece::DeployedPiece(const DeployedPiece* other) : pieceId(other->pieceId), origin(other->origin), rotation(other->rotation) {}

    std::vector<Util::Position> DeployedPiece::getOccupiedPositions() const {
        std::vector<Util::Position> positions;
        Piece piece = Piece::allPieces.at(pieceId);
        Piece::Shape shape = std::get<0>(piece.rotations.at(uint8_t(rotation)));

        for (auto path : shape) {
            positions.push_back(origin.move(path));
        }

        return positions;
    }
}