#include <stdexcept>
#include <bitset>

#include "Board.hpp"

namespace Model {

    BoardStatistics::BoardStatistics() : BoardStatistics(PieceColor::NONE) {}

    BoardStatistics::BoardStatistics(const PieceColor& color) 
        : color(color),
          pullFactor({ 0, 0, 0, 0 }),
          pushFactor({ 0, 0 }),
          freeCorners(0),
          friendlyBlockedCorners(0),
          opponentBlockedCorners(0),
          sharedEdges(0),
          friendlySharedEdges(0),
          opponentSharedEdges(0),
          dropPositions(0),
          opponentSharedDropPositions(0),
          dropSpread({}),
          usedDropPositions(0),
          alignment({}),
          ratedDropPositions({ 0, 0, 0, 0, 0, 0, 0 }) {}

    void BoardStatistics::reset() {
        pullFactor.fill(0);
        pushFactor.fill({ 0, 0 });
        freeCorners = 0;
        friendlyBlockedCorners = 0;
        opponentBlockedCorners = 0;
        sharedEdges = 0; 
        friendlySharedEdges = 0;
        dropPositions = 0;
        ratedDropPositions.fill(0);
        opponentSharedDropPositions = 0;
        dropSpread.fill({});
        usedDropPositions = 0;
        alignment.fill(0);
    }

    Board::Board() : statistics(), neighbours(), corners() {
        statistics = { BoardStatistics(PieceColor::RED), BoardStatistics(PieceColor::BLUE), BoardStatistics(PieceColor::GREEN), BoardStatistics(PieceColor::YELLOW) };

        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; ++x) {
                positions[y * 20 + x] = Util::Position(x, y);
            }
        }

        for (const Util::Position& position : positions) {
            for (const Util::Position& neighbour : position.getEdges()) {
                if (neighbour.x < 20 && neighbour.x > -1 && neighbour.y < 20 && neighbour.y > -1) {
                    neighbours[position.y * 20 + position.x].push_back(&positions[neighbour.y * 20 + neighbour.x]);
                }
            }

            for (const Util::Position& corner : position.getCorners()) {
                if (corner.x < 20 && corner.x > -1 && corner.y < 20 && corner.y > -1) {
                    corners[position.y * 20 + position.x].push_back(&positions[corner.y * 20 + corner.x]);
                }
            }
        }
    }

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

    const std::array<BoardStatistics, 4>& Board::getStatistics() const {
        // Reset statistics
        for (BoardStatistics& stats : statistics) {
            stats.reset();
        }

        const std::array<const Util::Position*, 4> startPositions { 
            &positions[399], 
            &positions[19 * 20], 
            &positions[0], 
            &positions[19] 
        };

        for (int y = 0; y < 20; ++y) {
            for (int x = 0; x < 20; ++x) {
                const PieceColor& color = at_unsafe(x, y);
                const uint8_t colorIdx = static_cast<uint8_t>(color) - 1;

                if (color != PieceColor::NONE) {
                    // If field is occupied calculate pull and push factor
                    for (int i = 0; i < 4; ++i) {
                        const int pull = statistics[colorIdx].pullFactor[i];
                        const int vecX = abs(x - startPositions[i]->x);
                        const int vecY = abs(y - startPositions[i]->y);
                        const int here = std::min(vecX, vecY);

                        statistics[colorIdx].pushFactor[i][0] += vecX;
                        statistics[colorIdx].pushFactor[i][1] += vecY;

                        if (here > pull) {
                            statistics[colorIdx].pullFactor[i] = here;
                        }
                    }

                    // Check if the piece is blocking a drop position
                    for (int i = 0; i < 4; ++i) {
                        uint8_t dropValue = dropPositions[i][y][x];
                        const PieceColor dropParent = static_cast<PieceColor>(i + 1);

                        if (dropValue > 0 && dropParent != color) {
                            const bool friendlyBlocked = 
                                (color == PieceColor::RED && dropParent == PieceColor::BLUE) || 
                                (color == PieceColor::BLUE && dropParent == PieceColor::RED) ||
                                (color == PieceColor::GREEN && dropParent == PieceColor::YELLOW) || 
                                (color == PieceColor::YELLOW && dropParent == PieceColor::GREEN);

                            if (friendlyBlocked) {
                                statistics[i].friendlyBlockedCorners += 1;
                            } else {
                                statistics[i].opponentBlockedCorners += 1;
                            }
                        }
                    }

                    if (dropPositions[colorIdx][y][x] > 0) {
                        statistics[colorIdx].usedDropPositions += 1;
                    }

                    statistics[colorIdx].alignment[0] += x;
                    statistics[colorIdx].alignment[1] += 19 - x;

                    //? Temporary unused for performance reasons
                    // Check for shared edges
                    // for (const Util::Position* neighbour : neighbours[getIndex(x, y)]) {
                    //     const PieceColor& neighbourColor = at_unsafe(neighbour->x, neighbour->y);

                    //     statistics[colorIdx].sharedEdges += neighbourColor != PieceColor::NONE && neighbourColor != color;

                    //     switch (color) {
                    //         case PieceColor::RED:
                    //             statistics[colorIdx].friendlySharedEdges += neighbourColor == PieceColor::BLUE;
                    //             statistics[colorIdx].opponentSharedEdges += neighbourColor == PieceColor::GREEN || neighbourColor == PieceColor::YELLOW;
                    //             break;
                    //         case PieceColor::BLUE:
                    //             statistics[colorIdx].friendlySharedEdges += neighbourColor == PieceColor::RED;
                    //             statistics[colorIdx].opponentSharedEdges += neighbourColor == PieceColor::GREEN || neighbourColor == PieceColor::YELLOW;
                    //             break;
                    //         case PieceColor::GREEN:
                    //             statistics[colorIdx].friendlySharedEdges += neighbourColor == PieceColor::YELLOW;
                    //             statistics[colorIdx].opponentSharedEdges += neighbourColor == PieceColor::BLUE || neighbourColor == PieceColor::RED;
                    //             break;
                    //         case PieceColor::YELLOW:
                    //             statistics[colorIdx].friendlySharedEdges += neighbourColor == PieceColor::GREEN;
                    //             statistics[colorIdx].opponentSharedEdges += neighbourColor == PieceColor::BLUE || neighbourColor == PieceColor::RED;
                    //             break;
                    //     }
                    // }
                } else {
                    std::bitset<2> colors{};

                    // If field is empty check if it is a drop position
                    for (int i = 0; i < 4; ++i) {
                        if (dropPositions[i][y][x] > 0) {
                            bool isValid = true;

                            // Do not include position in results if another piece of the same color is located at the edge of the position.
                            for (const Util::Position* edge : neighbours[getIndex(x, y)]) {
                                if (at_unsafe(edge->x, edge->y) == static_cast<PieceColor>(i + 1)) {
                                    isValid = false;
                                    break;
                                }
                            }

                            if (isValid) {
                                statistics[i].dropPositions += 1;

                                colors[colorIdx / 2] = true;

                                // number of free surrounding fields (0...8).
                                // 8 -> impossible because a drop position is always connected to at least one piece
                                int free = 0;

                                for (const Util::Position* neighbour : neighbours[getIndex(x, y)]) {
                                    free += at_unsafe(neighbour->x, neighbour->y) == PieceColor::NONE;
                                }

                                for (const Util::Position* corner : corners[getIndex(x, y)]) {
                                    free += at_unsafe(corner->x, corner->y) == PieceColor::NONE;
                                }

                                statistics[i].ratedDropPositions[free] += 1;

                                for (int c = 0; c < 4; ++c) {
                                    statistics[i].dropSpread[c][std::max(abs(x - startPositions[i]->x), abs(y - startPositions[i]->y))] += 1;
                                }
                            }

                            statistics[i].freeCorners += 1;
                        } 
                    }

                    if (colors[0] == true && colors[1] == true) {
                        statistics[colorIdx].opponentSharedDropPositions += 1;
                    }
                }
            }
        }

        return statistics;
    }

    int Board::getIndex(int x, int y) const {
        return y * 20 + x;
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

        os << std::dec;

        return os;
    }

}
