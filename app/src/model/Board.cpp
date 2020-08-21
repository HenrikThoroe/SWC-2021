#include <stdexcept>

#include "Board.hpp"

namespace Model {

    Board::Board() {}

    void Board::dropPiece(const DeployedPiece& piece) {
        const uint8_t colorIndex = static_cast<uint8_t>(piece.color) - 1;

        for (const Util::Position& pos : piece.getOccupiedPositions()) {
            fields[pos.y][pos.x] = piece.color;
            
            for (int i = 0; i < 4; ++i) {
                dropPositions[i][pos.y][pos.x] *= -1;
            }
        }

        for (const Util::Position& pos : piece.getAttachPoints()) {
            if (pos.x < 0 || pos.x > 19 || pos.y < 0 || pos.y > 19) {
                continue;
            }

            dropPositions[colorIndex][pos.y][pos.x] += 1;
        }
    }

    void Board::removePiece(const DeployedPiece& piece) {
        const uint8_t colorIndex = static_cast<uint8_t>(piece.color) - 1;

        for (const Util::Position& pos : piece.getOccupiedPositions()) {
            fields[pos.y][pos.x] = PieceColor::NONE;
            
            for (int i = 0; i < 4; ++i) {
                dropPositions[i][pos.y][pos.x] *= -1;
            }
        }

        for (const Util::Position& pos : piece.getAttachPoints()) {
            if (pos.x < 0 || pos.x > 19 || pos.y < 0 || pos.y > 19) {
                continue;
            }
            
            dropPositions[colorIndex][pos.y][pos.x] -= 1;
        }
    }

    void Board::makeDropPosition(const Util::Position& position, const PieceColor& color) {
        if (color == PieceColor::NONE || color == PieceColor::OBSTRUCTED) {
            return;
        }

        dropPositions[static_cast<uint8_t>(color) - 1][position.y][position.x] = 1;
    }

    const PieceColor& Board::at(const Util::Position& position) const {
        return at(position.x, position.y);
    }

    const PieceColor& Board::at(int x, int y) const {
        static const PieceColor& outOfRange = PieceColor::OBSTRUCTED;

        if (x < 0 || y < 0 || x > 19 || y > 19) {
            return outOfRange;
        }
        
        return fields[y][x];
    }  

    const PieceColor& Board::operator [] (const Util::Position& position) const {
        return fields[position.y][position.x];
    }

    std::vector<Util::Position> Board::getDropPositions(const PieceColor& color) const {
        if (color != PieceColor::NONE && color != PieceColor::OBSTRUCTED) {
            const RawFieldSet& fields = dropPositions[static_cast<uint8_t>(color) - 1];
            std::vector<Util::Position> results {};

            for (int row = 0; row < 20; ++row) {
                for (int col = 0; col < 20; ++col) {
                    if (fields[row][col] > 0) {
                        results.emplace_back(col, row);
                    }
                }
            }

            return results;
        }

        throw std::runtime_error("Cannot access drop positions. Only RED, BLUE, GREEN and YELLOW are allowed.");
    }

    bool Board::canDrop(const PieceColor& color, const Util::Position& position) const {
        return dropPositions[static_cast<uint8_t>(color) - 1][position.y][position.x] > 0;
    }

    bool Board::canDrop(const PieceColor& color, int x, int y) const { 
        return dropPositions[static_cast<uint8_t>(color) - 1][y][x] > 0;
    }

    std::ostream& operator << (std::ostream& os, const Board& board) {
        for (int row = 0; row < 20; ++row) {
            for (int col = 0; col < 20; ++col) {
                os << static_cast<int>(board.fields[row][col]);

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