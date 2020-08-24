#include <stdexcept>
#include <random>

#include "GameState.hpp"
#include "PieceCollection.hpp"
#include "bitAt.hpp"

namespace Model {

    GameState::GameState() : players({ Player(PlayerColor::BLUE), Player(PlayerColor::RED) }), board(), turn(0) {
        const Util::Position topLeft = Util::Position(0, 0);
        const Util::Position topRight = Util::Position(19, 0);
        const Util::Position bottomLeft = Util::Position(0, 19);
        const Util::Position bottomRight = Util::Position(19, 19);

        for (uint8_t c = 1; c <= 4; ++c) {
            const PieceColor color = static_cast<PieceColor>(c);

            board.makeDropPosition(topLeft, color);
            board.makeDropPosition(topRight, color);
            board.makeDropPosition(bottomLeft, color);
            board.makeDropPosition(bottomRight, color);
        }

        availablePieces.fill({ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } });
        allPieces.reserve(20 * 20 * 21 * 4 * 4);
        undeployablePiecesHistory.push(std::bitset<134400> {});

        for (uint8_t color = 0; color < 4; ++color) {
            for (uint8_t pieceId = 0; pieceId < 21; ++pieceId) {
                for (uint8_t rotation = 0; rotation < 4; ++rotation) {
                    for (int row = 0; row < 20; ++row) {
                        for (int col = 0; col < 20; ++col) {
                            allPieces.emplace_back(pieceId, Util::Position(col, row), static_cast<Rotation>(rotation), static_cast<PieceColor>(color + 1));
                        }
                    }
                }
            }
        }

        std::random_device rd;
        std::mt19937_64 eng(rd());
        std::uniform_int_distribution<uint64_t> distr;

        for (int i = 0; i < 134400; ++i) {
            hashpool[i] = distr(eng);
        }

        movesCache.reserve(2000);
    }

    const uint8_t& GameState::getTurn() const {
        return turn;
    }

    const Player& GameState::getCurrentPlayer() const {
        return players[turn % 2];
    }

    const PieceColor& GameState::getCurrentPieceColor() const {
        const int idx = turn % 4;
        return getCurrentPlayer().getPieceColors().at(idx > 1 ? 1 : 0);
    }

    void GameState::performMove(const Move& move) {
        undeployablePiecesHistory.push(undeployablePieces);
        availablePieces[static_cast<uint8_t>(move.color) - 1][move.pieceId] -= 1;
        board.dropPiece(move);
        performedMoves.push(move);
        turn += 1;

        hashValue ^= hashpool[createIndex(&move)];
    }

    void GameState::revertLastMove() {
        DeployedPiece& piece = performedMoves.top();

        availablePieces[static_cast<uint8_t>(piece.color) - 1][piece.pieceId] += 1;
        board.removePiece(piece);
        performedMoves.pop();
        turn -= 1;
        undeployablePieces = undeployablePiecesHistory.top();
        undeployablePiecesHistory.pop();

        hashValue ^= hashpool[createIndex(&piece)];
    }

    bool GameState::canBeDeployed(const DeployedPiece& piece) {
        return canBeDeployed(&piece);
    }

    bool GameState::canBeDeployed(const DeployedPiece* piece) {
        int index = createIndex(piece);

        if (undeployablePieces[index] == true) {
            return false;
        }

        for (const Util::Position& position : piece->getOccupiedPositions()) {

            if (position.x < 0 || position.x > 19 || position.y < 0 || position.y > 19) {
                undeployablePieces[index] = true;
                return false;
            }

            if (board[position] != PieceColor::NONE) {
                undeployablePieces[index] = true;
                return false;
            }

            for (const Util::Position& edge : position.getEdges()) {
                if (board.at(edge) == piece->color) {
                    undeployablePieces[index] = true;
                    return false;
                }
            }

        }

        return true;
    }

    inline int GameState::createIndex(const DeployedPiece* piece) const {
        return 
            piece->origin.x +
            piece->origin.y * 20 +
            static_cast<uint8_t>(piece->rotation) * 400 + 
            piece->pieceId * 1600 + 
            (static_cast<uint8_t>(piece->color) - 1) * 33600;
    }

    std::vector<const Move*> GameState::getPossibleMoves() {
        std::vector<const Move*> moves {};
        assignPossibleMoves(moves);
        return moves;
    }

    void GameState::assignPossibleMoves(std::vector<const Move*>& moves) {

        if (movesCache.contains(hashValue)) {
            moves = movesCache[hashValue].value;
            movesCache[hashValue].accesses += 1;
            movesCache[hashValue].turn = turn;
            return;
        }

        const PieceColor& color = getCurrentPieceColor();
        const uint8_t colorId = static_cast<uint8_t>(color) - 1;
        const std::vector<Util::Position> dropPositions = board.getDropPositions(color);
        int indexCache[5] = { 0, 0, 0, 0, (static_cast<uint8_t>(color) - 1) * 20 * 20 * 4 * 21 };
        std::bitset<134400> usedPieces {};

        // Reserve 400 items to prevent repeated resizing of moves vector
        moves.reserve(400);

        // Iterate all available drop positions for current color
        for (const Util::Position& dropPosition : dropPositions) {

            // Iterate all piece shapes
            for (int pieceId = 0; pieceId < 21; ++pieceId) {

                // Filter all shapes which are unavailable for current color
                if (availablePieces[colorId][pieceId] == 0) {
                    continue;
                }

                const Piece& piece = PieceCollection::getPiece(pieceId);

                indexCache[3] = pieceId * 1600;

                // Iterate all rotations
                for (const Rotation& rotation : piece.uniqueRotations) {
                    const Piece::AttachPoints& attachPoints = std::get<1>(piece.rotations[static_cast<uint8_t>(rotation)]);

                    indexCache[2] = static_cast<uint8_t>(rotation) * 400;

                    // Iterate all attach vectors of the shape 
                    for (const Piece::AttachPoint& info : attachPoints) {
                        const Util::Vector2D& offsetVector = info[1];

                        // Ensure a piece of the same color is located at the corner of the new piece
                        if (getTurn() > 3 && board[dropPosition + offsetVector] != color) {
                            continue;
                        }

                        const Util::Vector2D& attachVector = info[0];
                        const Util::Position origin = dropPosition - attachVector + offsetVector;

                        if (origin.y < 0 || origin.x < 0 || origin.y > 19 || origin.x > 19) {
                            continue;
                        }

                        // x + y * maxX + rotation * maxX * maxY + id * maxRotations * maxX * maxY + color * maxId * maxRotations * maxX * maxY
                        const int index = 
                            origin.x +
                            origin.y * 20 +
                            indexCache[2] + 
                            indexCache[3] + 
                            indexCache[4];

                        // Skip if the piece cannot be deployed or is already included
                        if (undeployablePieces[index] || usedPieces[index]) {
                            continue;
                        }

                        const DeployedPiece* deployed = &allPieces[index];

                        // Add piece to result vector if it can be deployed on the board
                        if (canBeDeployed(deployed)) {
                            moves.push_back(deployed);
                            usedPieces[index] = true;
                        }
                    }
                }
            }
        }

        movesCache[hashValue] = { moves, 0, turn };
    }

    uint64_t GameState::hash() const {
        return hashValue;
    }

    std::bitset<808> GameState::uniqueHash() const {
        std::bitset<808> out {};

        for (int row = 0; row < 20; ++row) {
            for (int col = 0; col < 20; ++col) {
                Util::Position pos = Util::Position(row, col);
                int idx = col + row * 20;
                uint8_t value = static_cast<uint8_t>(board.at(pos));

                for (int i = 0; i < 2; ++i) {
                    out[idx * 2 + i] = Util::bitAt(value, 7 - i);
                }
            }   
        }

        out[800] = Util::bitAt(turn, 2);
        out[801] = Util::bitAt(turn, 3);
        out[802] = Util::bitAt(turn, 4);
        out[803] = Util::bitAt(turn, 5);
        out[804] = Util::bitAt(turn, 6);
        out[805] = Util::bitAt(turn, 7);
        out[806] = Util::bitAt(static_cast<uint8_t>(getCurrentPieceColor()) - 1, 0);
        out[807] = Util::bitAt(static_cast<uint8_t>(getCurrentPieceColor()) - 1, 1);

        return out;
    }

    int GameState::evaluate() const {
        throw std::runtime_error("Not Implemented");
    }

    std::ostream& operator << (std::ostream& os, const GameState& state) {
        os << "Turn: " << static_cast<int>(state.turn) << std::endl;
        os << "Player: " << state.getCurrentPlayer().color << std::endl;
        os << "Color: " << state.getCurrentPieceColor() << " (" << static_cast<int>(state.getCurrentPieceColor()) << ")" << std::endl;
        os << "Available: ";
        
        for (int pieceId : state.availablePieces[static_cast<uint8_t>(state.getCurrentPieceColor()) - 1]) {
            os << pieceId << " ";
        }

        os << std::endl;

        os << "Board: " << std::endl << state.board;
        return os;
    }

}