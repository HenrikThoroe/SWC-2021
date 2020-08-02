#include "DeployedPiece.hpp"
#include "Position.hpp"
#include "PieceCollection.hpp"

namespace Model {

    DeployedPiece::DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation, PieceColor color) : pieceId(id), origin(origin), rotation(rotation), color(color) {
        const Piece& piece = PieceCollection::getPiece(pieceId);
        const Piece::Shape& shape = std::get<0>(piece.rotations.at(uint8_t(rotation)));
        const Piece::AttachPoints& attachPoints = std::get<1>(piece.rotations.at(uint8_t(rotation)));

        for (const auto& path : shape) {
            occupiedPositions.push_back(origin + path);
        }

        for (const auto& attachPoint : attachPoints) {
            const auto absolutePoint = origin + attachPoint.at(0);
            this->attachPoints.push_back(absolutePoint);
            this->validationPoints.push_back(absolutePoint + attachPoint.at(1));
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