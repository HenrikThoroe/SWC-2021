#pragma once

#include <inttypes.h>

#include "color.hpp"
#include "Rotation.hpp"
#include "Position.hpp"
#include "Vector2D.hpp"
#include "DeployedPiece.hpp"

namespace Model {

    /// A derived class from 'DeployedPiece' which can be initialized with a position on board and a vector pointing to origin.
    class Move: DeployedPiece {
        public: 
            Move(uint8_t pieceId, PieceColor color, Rotation rotation, Util::Vector2D vectorToOrigin, Util::Position dropPosition);
    };

}