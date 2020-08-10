#include <stdexcept>

#include "GameState.hpp"
#include "PieceCollection.hpp"

namespace Model {

    GameState::GameState() : turn(0), players({ Player(PlayerColor::BLUE), Player(PlayerColor::RED) }), board() {
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
        availablePieces[static_cast<int>(move.color) - 1][move.pieceId] -= 1;
        board.dropPiece(move);
        performedMoves.push(move);
        turn += 1;
    }

    void GameState::revertLastMove() {
        DeployedPiece& piece = performedMoves.top();

        availablePieces[static_cast<int>(piece.color) - 1][piece.pieceId] += 1;
        board.removePiece(piece);
        performedMoves.pop();
        turn -= 1;
    }

    bool GameState::canBeDeployed(const DeployedPiece& piece) const {
        for (const Util::Position& position : piece.getOccupiedPositions()) {
            if (position.x < 0 || position.x > 19 || position.y < 0 || position.y > 19) {
                return false;
            }

            if (board.at(position) != PieceColor::NONE) {
                return false;
            }

            for (const Util::Position& edge : position.getEdges()) {
                if (board.at(edge) == piece.color) {
                    return false;
                }
            }
        }

        return true;
    }

    std::vector<Move> GameState::getPossibleMoves() const {
        const PieceColor& color = getCurrentPieceColor();
        const uint8_t colorId = static_cast<uint8_t>(color) - 1;
        const std::vector<Util::Position> dropPositions = board.getDropPositions(color);
        std::vector<Move> moves {};

        // Reserve 300 items to prevent repeated resizing of moves vector
        moves.reserve(300);

        // Iterate all available drop positions for current color
        for (const Util::Position& dropPosition : dropPositions) {

            // Iterate all piece shapes
            for (int pieceId = 0; pieceId < 21; ++pieceId) {

                // Filter all shapes which are unavailable for current color
                if (availablePieces[colorId][pieceId] <= 0) {
                    continue;
                }

                const Piece& piece = PieceCollection::getPiece(pieceId);

                // Iterate all rotations
                for (const Rotation& rotation : piece.uniqueRotations) {
                    const Piece::AttachPoints& attachPoints = std::get<1>(piece.rotations[static_cast<uint8_t>(rotation)]);

                    // Iterate all attach vectors of the shape 
                    for (const Piece::AttachPoint& info : attachPoints) {
                        const Util::Vector2D& offsetVector = info[1];

                        if (getTurn() > 3 && board.at(dropPosition + offsetVector) != color) {
                            continue;
                        }

                        const Util::Vector2D& attachVector = info[0];
                        const Util::Position origin = dropPosition - attachVector + offsetVector;
                        DeployedPiece deployed = DeployedPiece(pieceId, origin, rotation, color, false);

                        // Calculate occupied fields to enable validity check
                        deployed.prepareOccupiedFields();

                        // Add piece to result vector if it can be deployed on the board
                        if (canBeDeployed(deployed)) {

                            // Finalize deployed piece when valid
                            deployed.prepareAttachPoints();
                            
                            moves.push_back(deployed);
                        }
                    }
                }
            }
        }

        return moves;
    }

    uint64_t GameState::hash() const {
        throw std::runtime_error("Not Implemented");
    }

    int GameState::evaluate() const {
        throw std::runtime_error("Not Implemented");
    }

    std::ostream& operator << (std::ostream& os, const GameState& state) {
        os << "Turn: " << static_cast<int>(state.turn) << std::endl;
        os << "Player: " << state.getCurrentPlayer().color << std::endl;
        os << "Color: " << state.getCurrentPieceColor() << std::endl;
        os << "Board: " << std::endl << state.board;
        return os;
    }

}