#pragma once

#include <inttypes.h>
#include <vector>

#include "Piece.hpp"
#include "Rotation.hpp"
#include "Position.hpp"
#include "color.hpp"

namespace Model {

    /// DeployedPiece contains the information to identify a piece on the board. 
    class DeployedPiece {
        public:
            /// The id of the corresenponding piece.
            const uint8_t pieceId;

            /// The origin of the piece. 
            const Util::Position origin;

            /// The rotation in which the piece has been deployed.
            const Rotation rotation;

            /// The color of the piece.
            const PieceColor color;

            DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation, PieceColor color);
            DeployedPiece(uint8_t pieceId, PieceColor color, Rotation rotation, Util::Vector2D vectorToOrigin, Util::Position dropPosition);
            DeployedPiece(const DeployedPiece& other);
            DeployedPiece(const DeployedPiece* other);

            const std::vector<Util::Position>& getOccupiedPositions() const;

            const std::vector<Util::Position>& getAttachPoints() const;

            const std::vector<Util::Position>& getValidationPoints() const;

        private:
            /// A set of all positions which are occupied by the piece.
            std::vector<Util::Position> occupiedPositions;

            /// A set of all positions where other pieces with the same color could be attached.
            std::vector<Util::Position> attachPoints;

            /// A set of all positions where another piece of the same color is expected. If this is not the case, the deployed piece is invalid.
            std::vector<Util::Position> validationPoints;
    };

}