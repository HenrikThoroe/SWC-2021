#include "Move.hpp"

namespace Model {

    Move::Move(uint8_t pieceId, PieceColor color, Rotation rotation, Util::Vector2D vectorToOrigin, Util::Position dropPosition) 
        : DeployedPiece(pieceId, dropPosition.move(vectorToOrigin), rotation, color) {}
        
}