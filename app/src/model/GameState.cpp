#include <stdexcept>
#include <random>

#include "GameState.hpp"
#include "PieceCollection.hpp"
#include "bitAt.hpp"

namespace Model {

    GameState::GameState(int initialPiece) : players({ Player(PlayerColor::BLUE), Player(PlayerColor::RED) }), board(), turn(0), initialPiece(initialPiece) {
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
        allPieces.reserve(20 * 20 * 21 * 4 * 8);
        undeployablePiecesHistory.push({});

        for (uint8_t color = 0; color < 4; ++color) {
            for (uint8_t pieceId = 0; pieceId < 21; ++pieceId) {
                for (uint8_t rotation = 0; rotation < 8; ++rotation) {
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

        for (int i = 0; i < 268800; ++i) {
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

    void GameState::performMove(const Move* move) {
        if (move != nullptr) {
            availablePieces[static_cast<uint8_t>(move->color) - 1][move->pieceId] -= 1;
            board.dropPiece(move);
            hashValue ^= hashpool[createIndex(move)];
            performedMoves.push(*move);
        } else {
            performedMoves.push(std::nullopt);
        }

        undeployablePiecesHistory.push(undeployablePieces);
        turn += 1;
    }

    void GameState::revertLastMove() {
        std::optional<DeployedPiece>& piece = performedMoves.top();

        if (piece.has_value()) {
            availablePieces[static_cast<uint8_t>(piece.value().color) - 1][piece.value().pieceId] += 1;
            board.removePiece(piece.value());
            hashValue ^= hashpool[createIndex(&piece.value())];
        }
        
        performedMoves.pop();
        turn -= 1;
        undeployablePieces = undeployablePiecesHistory.top();
        undeployablePiecesHistory.pop();
    }

    bool GameState::canBeDeployed(const DeployedPiece& piece) {
        return canBeDeployed(&piece);
    }

    bool GameState::canBeDeployed(const DeployedPiece* piece) {
        int index = createIndex(piece, false);

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

    inline int GameState::createIndex(const DeployedPiece* piece, bool includeColor) const {
        int idx = 
            piece->origin.x +
            piece->origin.y * 20 +
            static_cast<uint8_t>(piece->rotation) * 400 + 
            piece->pieceId * 3200;

        if (includeColor) {
            idx += (static_cast<uint8_t>(piece->color) - 1) * 67200;
        }

        return idx;
    }

    std::vector<const Move*> GameState::getPossibleMoves() {
        // std::cout << "Get Moves" << std::endl;
        std::vector<const Move*> moves {};
        assignPossibleMoves(moves);
        // std::cout << "Got Moves" << std::endl;
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
        int indexCache[5] = { 0, 0, 0, 0, (static_cast<uint8_t>(color) - 1) * 20 * 20 * 8 * 21 };
        std::bitset<67200> usedPieces {};

        // Reserve 550 items to prevent repeated resizing of moves vector
        moves.reserve(550);

        // Iterate all available drop positions for current color
        for (const Util::Position& dropPosition : dropPositions) {

            // Iterate all piece shapes
            for (int pieceId = 0; pieceId < 21; ++pieceId) {

                // Filter all shapes which are unavailable for current color
                if (availablePieces[colorId][pieceId] == 0 || (getTurn() < 4 && pieceId != initialPiece)) {
                    continue;
                }

                const Piece& piece = PieceCollection::getPiece(pieceId);

                indexCache[3] = pieceId * 3200;

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

                        // x + y * maxX + rotation * maxX * maxY + id * maxRotations * maxX * maxY
                        const int index = 
                            origin.x +
                            origin.y * 20 +
                            indexCache[2] + 
                            indexCache[3];

                        if (index >= 67200) {
                            std::cerr << index << std::endl;
                        }

                        // Skip if the piece cannot be deployed or is already included
                        if (undeployablePieces[index] || usedPieces[index]) {
                            continue;
                        }

                        const DeployedPiece* deployed = &allPieces[index + indexCache[4]];

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

        // Iterate all positions
        for (int row = 0; row < 20; ++row) {
            for (int col = 0; col < 20; ++col) {
                Util::Position pos = Util::Position(row, col);
                int idx = col + row * 20;
                uint8_t value = static_cast<uint8_t>(board.at(pos));

                // Iterate last two bits of color at position
                for (int i = 0; i < 2; ++i) {
                    out[idx * 2 + i] = Util::bitAt(value, 7 - i);
                }
            }   
        }

        // Add the turn to the hash value. Only the last 6 bits are important
        for (int i = 2; i < 8; ++i) {
            out[800 + (i - 2)] = Util::bitAt(turn, i);
        }

        // Add current piece color to the hash 
        out[806] = Util::bitAt(static_cast<uint8_t>(getCurrentPieceColor()) - 1, 0);
        out[807] = Util::bitAt(static_cast<uint8_t>(getCurrentPieceColor()) - 1, 1);

        return out;
    }

    void GameState::freeMemory(float percent) {
        float normalizedPercent = percent > 1 ? 1 : percent < 0 ? 0 : percent;
        uint64_t targetSize = static_cast<uint64_t>(static_cast<float>(movesCache.size()) * (1 - normalizedPercent));
        std::vector<std::vector<uint64_t>> accessMap {};

        for (const std::pair<uint64_t, Model::GameState::MoveCacheEntry>& entry : movesCache) {
            if (entry.second.turn < turn) {
                movesCache.erase(entry.first);
            } else {
                while (entry.second.accesses >= accessMap.size()) {
                    accessMap.push_back({});
                }
                
                accessMap.at(entry.second.accesses).push_back(entry.first);
            }
        }

        for (uint64_t index = 0; index < accessMap.size(); ++index) {
            for (const uint64_t& key : accessMap.at(index)) {

                //TODO: In some szenarios, when many entries have to be erased (4GB+), `erase` throws an error. Until the reason is determined the error should be catched.
                try {
                    movesCache.erase(key);
                } catch (const std::bad_alloc&) {
                    std::cerr << "Bad Alloc when Freeing Game State Memory" << std::endl;
                    continue;
                }

                if (movesCache.size() <= targetSize) {
                    break;
                }
            }

            if (movesCache.size() <= targetSize) {
                break;
            }
        }
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