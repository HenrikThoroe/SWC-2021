#include "Piece.hpp"

namespace Model {

    Piece::Piece(uint8_t id, char* name, uint8_t size, std::vector<Rotation> uniqueRotations, std::vector<ShapeRotation> rotationValues, std::array<int, 8> rotations)
        : id(id), name(name), size(size), uniqueRotations(uniqueRotations), rotationValues(rotationValues), rotations(rotations) {
    }

    const Piece::ShapeRotation& Piece::getRotation(const Rotation& rotation) const {
        return this->rotationValues[rotations[static_cast<uint8_t>(rotation)]];
    }

    const Piece:: ShapeRotation& Piece::getRotation(uint8_t rotationId) const {
        return this->rotationValues[rotations[rotationId]];
    }

}