#include "DeployedPiece.hpp"
#include "Position.hpp"

namespace Model {

    DeployedPiece::DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation) : pieceId(id), origin(origin), rotation(rotation) {
        Piece piece = Piece::allPieces.at(pieceId);
        Piece::Shape shape = std::get<0>(piece.rotations.at(uint8_t(rotation)));
        Piece::AttachPoints attachPoints = std::get<1>(piece.rotations.at(uint8_t(rotation)));

        for (auto path : shape) {
            occupiedPositions.emplace_back(origin.move(path));
        }

        for (auto attachPointPath : attachPoints.at(0)) {
            attachPoints.emplace_back(origin.move(attachPointPath));
        }

        for (auto validationPointPath : attachPoints.at(1)) {
            validationPoints.emplace_back(origin.move(validationPointPath));
        }
    }

    DeployedPiece::DeployedPiece(const DeployedPiece& other) : DeployedPiece(other.pieceId, other.origin, other.rotation) {}

    DeployedPiece::DeployedPiece(const DeployedPiece* other) : DeployedPiece(other->pieceId, other->origin, other->rotation) {}

    const std::vector<Util::Position>& DeployedPiece::getOccupiedPositions() const {
        return occupiedPositions;
    }

    const std::vector<Util::Position>& DeployedPiece::getAttachPoints() const {
        return attachPoints;
    }

    const std::vector<Util::Position>& DeployedPiece::getValidationPoints() const {
        return validationPoints;
    }
}