#pragma once

#include <inttypes.h>
#include <vector>

#include "Piece.hpp"
#include "Rotation.hpp"
#include "Position.hpp"

namespace Model {

    /// DeployedPiece contains the information to identify a piece on the board. 
    class DeployedPiece {
        public:
            /// The id of the corresenponding piece.
            uint8_t pieceId;

            /// The origin of the piece. 
            Util::Position origin;

            /// The rotation in which the piece has been deployed.
            Rotation rotation;

            DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation);
            DeployedPiece(const DeployedPiece& other);
            DeployedPiece(const DeployedPiece* other);

            std::vector<Util::Position> getOccupiedPositions() const;
    };

}