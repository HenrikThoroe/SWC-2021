#include "DeployedPiece.hpp"
#include "Position.hpp"
#include "PieceCollection.hpp"

namespace Model {

    DeployedPiece::DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation, PieceColor color) : pieceId(id), origin(origin), rotation(rotation), color(color) {
        Piece piece = PieceCollection::getPiece(pieceId);
        Piece::Shape shape = std::get<0>(piece.rotations.at(uint8_t(rotation)));
        Piece::AttachPoints attachPoints = std::get<1>(piece.rotations.at(uint8_t(rotation)));

        for (auto path : shape) {
            occupiedPositions.emplace_back(origin + path);
        }

        for (auto attachPointPath : attachPoints.at(0)) {
            attachPoints.emplace_back(origin + attachPointPath);
        }

        for (auto validationPointPath : attachPoints.at(1)) {
            validationPoints.emplace_back(origin + validationPointPath);
        }
    }

    DeployedPiece::DeployedPiece(const DeployedPiece& other) : DeployedPiece(other.pieceId, other.origin, other.rotation, other.color) {}

    DeployedPiece::DeployedPiece(const DeployedPiece* other) : DeployedPiece(other->pieceId, other->origin, other->rotation, other->color) {}

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