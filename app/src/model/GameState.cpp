#include <stdexcept>
#include <random>

#include "GameState.hpp"
#include "PieceCollection.hpp"
#include "bitAt.hpp"
#include "filterMap.hpp"

namespace Model {

    GameState::GameState(int initialPiece) : players({ Player(PlayerColor::BLUE), Player(PlayerColor::RED) }), board(), turn(0), initialPiece(initialPiece) {
        const Util::Position topLeft = Util::Position(0, 0);
        const Util::Position topRight = Util::Position(Constants::BOARD_COLUMNS - 1, 0);
        const Util::Position bottomLeft = Util::Position(0, Constants::BOARD_ROWS - 1);
        const Util::Position bottomRight = Util::Position(Constants::BOARD_COLUMNS - 1, Constants::BOARD_ROWS - 1);

        for (uint8_t c = 1; c <= 4; ++c) {
            const PieceColor color = static_cast<PieceColor>(c);

            board.makeDropPosition(topLeft, color);
            board.makeDropPosition(topRight, color);
            board.makeDropPosition(bottomLeft, color);
            board.makeDropPosition(bottomRight, color);
        }

        availablePieces.fill({ { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 } });
        allPieces.reserve(Constants::PIECE_VARIANTS);

        for (uint8_t color = 0; color < 4; ++color) {
            for (uint8_t pieceId = 0; pieceId < Constants::PIECE_SHAPES; ++pieceId) {
                for (uint8_t rotation = 0; rotation < 8; ++rotation) {
                    for (int row = 0; row < Constants::BOARD_ROWS; ++row) {
                        for (int col = 0; col < Constants::BOARD_COLUMNS; ++col) {
                            allPieces.emplace_back(pieceId, Util::Position(col, row), static_cast<Rotation>(rotation), static_cast<PieceColor>(color + 1));
                        }
                    }
                }
            }
        }

        std::random_device rd;
        std::mt19937_64 eng(rd());
        std::uniform_int_distribution<uint64_t> distr;

        for (int i = 0; i < Constants::PIECE_VARIANTS; ++i) {
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

    const Player& GameState::getLastPlayer() const {
        if (turn < 1) {
            throw std::runtime_error("No last player available.");
        }

        return players[(turn - 1) % 2];
    }

    const PieceColor& GameState::getLastPieceColor() const {
        const int idx = (turn - 1) % 4;
        return getLastPlayer().getPieceColors().at(idx > 1 ? 1 : 0);
    }

    void GameState::update(std::optional<uint32_t> move) {
        if (move) {
            performMove(&allPieces[move.value()]);
        } else {
            performMove(nullptr);
        }
    }

    void GameState::performMove(const Move* move) {
        if (move != nullptr) {
            pushHistory[static_cast<uint8_t>(move->color) - 1].push(move->pieceId);
            availablePieces[static_cast<uint8_t>(move->color) - 1][move->pieceId] -= 1;
            board.dropPiece(move);
            hashValue ^= hashpool[createIndex(move)];
            performedMoves.push(*move);
        } else {
            performedMoves.push(std::nullopt);
        }

        turn += 1;
    }

    void GameState::revertLastMove() {
        std::optional<DeployedPiece>& piece = performedMoves.top();

        if (piece.has_value()) {
            pushHistory[static_cast<uint8_t>(piece.value().color) - 1].pop();
            availablePieces[static_cast<uint8_t>(piece.value().color) - 1][piece.value().pieceId] += 1;
            board.removePiece(piece.value());
            hashValue ^= hashpool[createIndex(&piece.value())];
        }
        
        performedMoves.pop();
        turn -= 1;
    }

    bool GameState::canBeDeployed(const DeployedPiece& piece) {
        return canBeDeployed(&piece);
    }

    bool GameState::canBeDeployed(const DeployedPiece* piece) {
        // A skip move can always be performed / No piece can always be deployed
        if (piece == nullptr) {
            return true;
        } 

        for (const Util::Position& position : piece->getOccupiedPositions()) {

            if (position.x < 0 || position.x > 19 || position.y < 0 || position.y > 19) {
                return false;
            }

            if (board[position] != PieceColor::NONE) {
                return false;
            }

            for (const Util::Position& edge : position.getEdges()) {
                if (board.at(edge) == piece->color) {
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
        std::vector<const Move*> moves {};
        assignPossibleMoves(moves);
        return moves;
    }

    void GameState::assignPossibleMoves(std::vector<const Move*>& moves) {

        if (movesCache.contains(hashValue) && movesCache[hashValue].turn % 4 == turn % 4) {
            moves = movesCache[hashValue].value;
            movesCache[hashValue].accesses += 1;
            movesCache[hashValue].turn = turn;
            return;
        }

        const PieceColor& color = getCurrentPieceColor();
        const uint8_t colorId = static_cast<uint8_t>(color) - 1;
        const std::vector<Util::Position> dropPositions = board.getDropPositions(color);
        int indexCache[5] = { 0, 0, 0, 0, (static_cast<uint8_t>(color) - 1) * 20 * 20 * 8 * 21 };
        std::bitset<Constants::PIECE_VARIANTS_NO_COLOR> usedPieces {};

        // Reserve 550 items to prevent repeated resizing of moves vector
        moves.reserve(550);
        
        if (turn > 3) {
            moves.push_back(nullptr);
        }

        auto allowsMoreThanOneField = [&color, this](const Util::Position& position) {

            // The corners of the position, starting at top right and rotating clockwise
            const std::array<Util::Position, 4> corners = {
                Util::Position(position.x + 1, position.y - 1),
                Util::Position(position.x + 1, position.y + 1),
                Util::Position(position.x - 1, position.y + 1),
                Util::Position(position.x - 1, position.y - 1)
            };
            
            // Indicates which corner is not blocked by a piece of the same color
            std::bitset<4> notBlocked {};

            for (int i = 0; i < 4; ++i) {
                notBlocked[i] = board.at(corners[i]) != color;
            }

            // Top right and bottom right are not blocked => check if edge at the right is possible drop position
            if (notBlocked[0] && notBlocked[1]) {
                const Util::Position middle = Util::Position(position.x + 1, position.y);
                const Util::Position edge = Util::Position(position.x + 2, position.y);
                
                // If a piece at 'position' and at position + (1; 0) can be droped at least a piece of size two is possible
                if (board.at(middle) == PieceColor::NONE && board.at(edge) != color) {
                    return true;
                }
            }

            // bottom right and bottom left
            if (notBlocked[1] && notBlocked[2]) {
                const Util::Position middle = Util::Position(position.x, position.y + 1);
                const Util::Position edge = Util::Position(position.x, position.y + 2);
                
                if (board.at(middle) == PieceColor::NONE && board.at(edge) != color) {
                    return true;
                }
            }

            // bottom left and top left
            if (notBlocked[2] && notBlocked[3]) {
                const Util::Position middle = Util::Position(position.x - 1, position.y);
                const Util::Position edge = Util::Position(position.x - 2, position.y);

                if (board.at(middle) == PieceColor::NONE && board.at(edge) != color) {
                    return true;
                }
            }

            // top left and top right
            if (notBlocked[3] && notBlocked[0]) {
                const Util::Position middle = Util::Position(position.x, position.y - 1);
                const Util::Position edge = Util::Position(position.x, position.y - 2);
                
                if (board.at(middle) == PieceColor::NONE && board.at(edge) != color) {
                    return true;
                }
            }

            return false;
        };

        // Iterate all available drop positions for current color
        for (const Util::Position& dropPosition : dropPositions) {

            bool monoOnly = !allowsMoreThanOneField(dropPosition);

            // Iterate all piece shapes
            for (int pieceId = 0; pieceId < Constants::PIECE_SHAPES; ++pieceId) {

                if (pieceId > 0 && monoOnly) {
                    break;
                }

                // Filter all shapes which are unavailable for current color
                if (availablePieces[colorId][pieceId] == 0 || (getTurn() < 4 && pieceId != initialPiece)) {
                    continue;
                }

                const Piece& piece = PieceCollection::getPiece(pieceId);

                indexCache[3] = pieceId * 3200;

                // Iterate all rotations
                for (const Rotation& rotation : piece.uniqueRotations) {
                    const Piece::AttachPoints& attachPoints = std::get<1>(piece.getRotation(rotation));

                    indexCache[2] = static_cast<uint8_t>(rotation) * 400;

                    // Iterate all attach vectors of the shape 
                    for (const Piece::AttachPoint& info : attachPoints) {
                        const Util::Vector2D& offsetVector = info[1];

                        // Ensure a piece of the same color is located at the corner of the new piece
                        //! IMPORTANT: By calling the subscript operator a false positive is possible. Such pieces will be filtered out by canBeDeployed.
                        if (getTurn() > 3 && board[dropPosition + offsetVector] != color) {
                            continue;
                        }

                        const Util::Vector2D& attachVector = info[0];
                        const Util::Position origin = dropPosition - attachVector + offsetVector;

                        if (origin.y < 0 || origin.x < 0 || origin.y > 19 || origin.x > 19) {
                            continue;
                        }

                        // x + y * maxX + rotation * maxX * maxY + id * maxRotations * maxX * maxY
                        const int index = (origin.x + origin.y * 20) + (indexCache[2] + indexCache[3]);

                        // Skip if the piece is already included
                        if (usedPieces[index]) {
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

        const std::function<bool(const uint64_t&, const MoveCacheEntry&)> filter = [this, &accessMap] (const uint64_t& key, const MoveCacheEntry& entry) {
            if (entry.turn < turn) {
                return true;
            } else {
                while (entry.accesses >= accessMap.size()) {
                    accessMap.push_back({});
                }
                
                accessMap.at(entry.accesses).push_back(key);
            }

            return false;
        };

        Util::filterMap(movesCache, filter);

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

    int GameState::evaluate(const PlayerColor& player, bool gameOver) const {
        const std::array<PieceColor, 2>& colors = players[static_cast<uint8_t>(player)].getPieceColors();
        const std::array<PieceColor, 2>& opponentColors = players[!static_cast<uint8_t>(player)].getPieceColors();
        int score = 0;
        int opponentScore = 0;

        // An offset to reduce score ossizalition. 
        // When the own player performed the last move (player != getCurrentPlayer().color) the opponent is lagging one piece behind.
        // Therefore the turn is adjusted by 1 to give the naturally fewer points of the opponent a higher rating.
        int normalizationOffset = (player == getCurrentPlayer().color) ? -1 : 1;

        for (const PieceColor& color : colors) {
            // Iterate all shapes
            for (uint8_t id = 0; id < Constants::PIECE_SHAPES; ++id) {

                // Check if the shape has been deployed
                if (availablePieces[static_cast<uint8_t>(color) - 1][id] == 0) {

                    // Add the size of the shape to the score
                    score += PieceCollection::getPiece(id).size;
                }
            }

            // Check if all pieces have been deployed
            if (pushHistory[static_cast<uint8_t>(color) - 1].size() == Constants::PIECE_SHAPES) {
                score += 15;

                // Check if the last deployed piece is the MONOMINO
                if (pushHistory[static_cast<uint8_t>(color) - 1].top() == 0) {
                    score += 5;
                }
            }
        }

        for (const PieceColor& color : opponentColors) {
            // Iterate all shapes
            for (uint8_t id = 0; id < Constants::PIECE_SHAPES; ++id) {

                // Check if the shape has been deployed
                if (availablePieces[static_cast<uint8_t>(color) - 1][id] == 0) {

                    // Add the size of the shape to the score
                    opponentScore += PieceCollection::getPiece(id).size;
                }
            }

            // Check if all pieces have been deployed
            if (pushHistory[static_cast<uint8_t>(color) - 1].size() == Constants::PIECE_SHAPES) {
                opponentScore += 15;

                // Check if the last deployed piece is the MONOMINO
                if (pushHistory[static_cast<uint8_t>(color) - 1].top() == 0) {
                    opponentScore += 5;
                }
            }
        }

        if (isGameOver() || gameOver) {
            if (score > opponentScore) {
                return Constants::WIN_POINTS + score;
            } else if (score < opponentScore) {
                return Constants::LOSE_POINTS - 10000 + score;
            } else {
                return 0;
            }
        }

        // The own score based on the current turn
        const int roundBasedScore = (110 - (100 - turn)) * score;

        // The opponent score based on the current turn and normalized
        const int roundBasedOpponentScore = (110 - (100 + normalizationOffset - turn)) * opponentScore;

        /// The more pieces deployed the better
        const int deployedPieceFactor = (pushHistory[static_cast<uint8_t>(colors[0]) - 1].size() + pushHistory[static_cast<uint8_t>(colors[1]) - 1].size()) * 20;

        return roundBasedScore - roundBasedOpponentScore + deployedPieceFactor;
    }

    bool GameState::isGameOver() const {
        if (turn >= 100) {
            return true;
        }  
        
        if (turn >= Constants::PIECE_SHAPES * 4) {
            for (int p = 0; p < 4; ++p) {
                if (pushHistory[p].size() == Constants::PIECE_SHAPES) {
                    return true;
                }
            }
        }

        return false;
    }

    std::ostream& operator << (std::ostream& os, const GameState& state) {
        os << "Turn: " << static_cast<int>(state.turn) << std::endl;
        os << "Player: " << state.getCurrentPlayer().color << std::endl;
        os << "Color: " << state.getCurrentPieceColor() << " (" << static_cast<int>(state.getCurrentPieceColor()) << ")" << std::endl;
        os << "Available: ";
        
        for (int pieceId = 0; pieceId < Constants::PIECE_SHAPES; ++pieceId) {
            if (state.availablePieces[static_cast<uint8_t>(state.getCurrentPieceColor()) - 1][pieceId] != 0) {
                os << PieceCollection::getPiece(pieceId).name << " ";
            }
        }

        os << std::endl;

        os << "Board: " << std::endl << state.board;
        return os;
    }

}
