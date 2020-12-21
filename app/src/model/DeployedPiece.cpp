#include "DeployedPiece.hpp"

#include "Position.hpp"
#include "PieceCollection.hpp"

namespace Model {

    DeployedPiece::DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation, PieceColor color, bool initializeFields) : pieceId(id), origin(origin), rotation(rotation), color(color) {
        if (initializeFields) {
            prepareAttachPoints();
            prepareOccupiedFields();
        }
    }

    DeployedPiece::DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation, PieceColor color, std::vector<Util::Position> occupiedPositions, std::vector<Util::Position> attachPoints) : 
        pieceId(id), origin(origin), rotation(rotation), color(color) {
            this->occupiedPositions = occupiedPositions;
            this->attachPoints = attachPoints;
    }

    void DeployedPiece::prepareOccupiedFields() {
        const Piece& piece = PieceCollection::getPiece(pieceId);
        const Piece::Shape& shape = std::get<0>(piece.getRotation(rotation));

        for (const Util::Vector2D& path : shape) {
            occupiedPositions.push_back(origin + path);
        }
    }

    void DeployedPiece::prepareAttachPoints() {
        const Piece& piece = PieceCollection::getPiece(pieceId);
        const Piece::AttachPoints& attachPoints = std::get<1>(piece.getRotation(rotation));

        for (const Piece::AttachPoint& attachPoint : attachPoints) {
            const Util::Position absolutePoint = origin + attachPoint.at(0);
            this->attachPoints.push_back(absolutePoint);
        }
    }

    DeployedPiece::DeployedPiece(uint8_t pieceId, PieceColor color, Rotation rotation, Util::Vector2D vectorToOrigin, Util::Position dropPosition) 
        : DeployedPiece(pieceId, dropPosition.move(vectorToOrigin), rotation, color) {}

    DeployedPiece::DeployedPiece(const DeployedPiece& other) : DeployedPiece(other.pieceId, other.origin, other.rotation, other.color, other.occupiedPositions, other.attachPoints) {}

    DeployedPiece::DeployedPiece(const DeployedPiece* other) : DeployedPiece(other->pieceId, other->origin, other->rotation, other->color, other->occupiedPositions, other->attachPoints) {}

    const std::vector<Util::Position>& DeployedPiece::getOccupiedPositions() const {
        return occupiedPositions;
    }

    const std::vector<Util::Position>& DeployedPiece::getAttachPoints() const {
        return attachPoints;
    }

    int DeployedPiece::index(bool includeColor) const {
        int idx = 
            origin.x +
            origin.y * 20 +
            static_cast<uint8_t>(rotation) * 400 + 
            pieceId * 3200;

        if (includeColor) {
            idx += (static_cast<uint8_t>(color) - 1) * 67200;
        }

        return idx;
    }

    std::ostream& operator << (std::ostream& os, const DeployedPiece& piece) {
        os << "DeployedPiece {";
        os << " id: " << static_cast<int>(piece.pieceId);
        os << ", origin: " << piece.origin;
        os << ", color: " << piece.color;
        os << ", rotation: " << static_cast<int>(piece.rotation) << " }";

        return os;
    }

}
