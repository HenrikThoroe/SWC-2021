#include "Board.hpp"

namespace Model {

    Board::Board() {}

    void Board::dropPiece(const DeployedPiece& piece) {
        for (const Util::Position& pos : piece.getOccupiedPositions()) {
            fields[pos.x][pos.y] = uint8_t(piece.color);
            
            for (int i = 0; i < 4; ++i) {
                dropPositions[i][pos.x][pos.y] *= -1;
            }
        }

        for (const Util::Position& pos : piece.getAttachPoints()) {
            dropPositions[uint8_t(piece.color)][pos.x][pos.y] += 1;
        }
    }

    void Board::removePiece(const DeployedPiece& piece) {
        for (const Util::Position& pos : piece.getOccupiedPositions()) {
            fields[pos.x][pos.y] = 0;
            
            for (int i = 0; i < 4; ++i) {
                dropPositions[i][pos.x][pos.y] *= -1;
            }
        }

        for (const Util::Position& pos : piece.getAttachPoints()) {
            dropPositions[uint8_t(piece.color)][pos.x][pos.y] -= 1;
        }
    }

}