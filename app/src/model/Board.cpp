#include <stdexcept>

#include "Board.hpp"

namespace Model {

    Board::Board() {}

    void Board::dropPiece(const DeployedPiece& piece) {
        const uint8_t colorIndex = static_cast<uint8_t>(piece.color) - 1;

        for (const Util::Position& pos : piece.getOccupiedPositions()) {
            fields[pos.y][pos.x] = piece.color;
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

    const PieceColor& Board::at_unsafe(int x, int y) const {
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
                    const bool isPossible = fields[row][col] > 0;
                    const bool isNotOccupied = this->fields[row][col] == PieceColor::NONE;

                    if (isPossible && isNotOccupied) {
                        const Util::Position position = Util::Position(col, row);
                        const std::array<Util::Position, 4> edges = position.getEdges();
                        bool isValid = true;

                        // Do not include position in results if another piece of the same color is located at the edge of the position.
                        for (const Util::Position& edge : edges) {
                            if (at(edge) == color) {
                                isValid = false;
                                break;
                            }
                        }

                        if (isValid) {
                            results.push_back(position);
                        }
                    }
                }
            }

            return results;
        }

        throw std::runtime_error("Cannot access drop positions. Only RED, BLUE, GREEN and YELLOW are allowed.");
    }

    int Board::estimateDropPositions(const PieceColor& firstColor, const PieceColor& secondColor) const {
        const RawFieldSet& firstFields = dropPositions[static_cast<uint8_t>(firstColor) - 1];
        const RawFieldSet& secondFields = dropPositions[static_cast<uint8_t>(secondColor) - 1];
        int count = 0;

        for (int row = 0; row < 20; ++row) {
            for (int col = 0; col < 20; ++col) {
                const bool firstIsPossible = firstFields[row][col] > 0;
                const bool secondIsPossible = secondFields[row][col] > 0;
                const bool isNotOccupied = this->fields[row][col] == PieceColor::NONE;

                if ((firstIsPossible || secondIsPossible) && isNotOccupied) {
                    const Util::Position position = Util::Position(col, row);
                    const std::array<Util::Position, 4> edges = position.getEdges();
                    bool valid = 2;

                    // Do not include position in results if another piece of the same color is located at the edge of the position.
                    for (const Util::Position& edge : edges) {
                        const PieceColor& color = at(edge);
                        if (color == firstColor) {
                            valid -= 1;
                        }
                        if (color == secondColor) {
                            valid -= 1;
                        }
                    }

                    if (valid > 0) {
                        count += 1;
                    }
                }
            }
        }

        return count;
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

                switch (board.fields[row][col]) {
                    case PieceColor::RED:
                        os << "\033[1;31m";
                        break;
                    case PieceColor::GREEN:
                        os << "\033[1;32m";
                        break;
                    case PieceColor::BLUE:
                        os << "\033[1;34m";
                        break;
                    case PieceColor::YELLOW:
                        os << "\033[1;33m";
                        break;
                }

                uint8_t indicator = 0;

                for (uint8_t c = 0; c < 4; ++c) {
                    const PieceColor color = static_cast<PieceColor>(c + 1);

                    if (board.canDrop(color, col, row)) {
                        indicator ^= (1 << c);
                    }
                }

                if (board.fields[row][col] != PieceColor::NONE) {
                    os << static_cast<int>(board.fields[row][col]);
                } else {
                    os << std::hex << static_cast<int>(indicator);
                }

                os << "\033[0m";

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
