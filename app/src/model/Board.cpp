#include "Board.hpp"

namespace Model {

    Board::Board() {}

    void Board::dropPiece(const DeployedPiece& piece) {
        for (const Util::Position& pos : piece.getOccupiedPositions()) {
            fields[pos.y][pos.x] = uint8_t(piece.color);
            
            for (int i = 0; i < 4; ++i) {
                dropPositions[i][pos.y][pos.x] *= -1;
            }
        }

        for (const Util::Position& pos : piece.getAttachPoints()) {
            dropPositions[uint8_t(piece.color)][pos.y][pos.x] += 1;
        }
    }

    void Board::removePiece(const DeployedPiece& piece) {
        for (const Util::Position& pos : piece.getOccupiedPositions()) {
            fields[pos.y][pos.x] = 0;
            
            for (int i = 0; i < 4; ++i) {
                dropPositions[i][pos.y][pos.x] *= -1;
            }
        }

        for (const Util::Position& pos : piece.getAttachPoints()) {
            dropPositions[uint8_t(piece.color)][pos.y][pos.x] -= 1;
        }
    }

    std::ostream& operator << (std::ostream& os, const Board& board) {
        for (int row = 0; row < 20; ++row) {
            for (int col = 0; col < 20; ++col) {
                os << int(board.fields[row][col]);

                if (col < 19) {
                    os << " | ";
                }
            }

            if (row < 19) {
                os << std::endl;
            
                for (int i = 0; i < 77; ++i) {
                    os << "-";
                }

                os << std::endl;
            }
        }

        return os;
    }

}