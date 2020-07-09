#include "Board.hpp"

namespace Model {

    Board::Board() {}

    void Board::dropPiece(const DeployedPiece& piece) {
        for (auto pos : piece.getOccupiedPositions()) {
            fields[pos.x][pos.y] = 1;
            
            for (int i = 0; i < 4; ++i) {
                dropPositions[i][pos.x][pos.y] *= -1;
            }
        }

        for (auto pos : piece.getAttachPoints()) {
            dropPositions[uint8_t(piece.color)][pos.x][pos.y] += 1;
        }
    }

}