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
        const std::vector<Util::Position> dropPositions = board.getDropPositions(color);
        std::vector<Move> moves {};

        // Iterate all available drop positions for current color
        for (const Util::Position& dropPosition : dropPositions) {

            // Iterate all piece shapes
            for (int pieceId = 0; pieceId < 21; ++pieceId) {

                // Filter all shapes which are unavailable for current color
                if (availablePieces[static_cast<int>(color) - 1][pieceId] <= 0) {
                    continue;
                }

                // Iterate all rotations
                for (uint8_t rot = 0; rot < 4; ++rot) {
                    const Rotation rotation = static_cast<Rotation>(rot);
                    const Piece& piece = PieceCollection::getPiece(pieceId);
                    const Piece::AttachPoints& attachPoints = std::get<1>(piece.rotations[rot]);

                    // Iterate all attach vectors of the shape 
                    for (const Piece::AttachPoint& info : attachPoints) {
                        const Util::Vector2D& offsetVector = info[1];
                        const Util::Vector2D& attachVector = info[0];
                        const Util::Position origin = dropPosition - attachVector + offsetVector;
                        const DeployedPiece deployed = DeployedPiece(pieceId, origin, rotation, color);

                        // Add piece to result vector if it can be deployed on the board
                        if (canBeDeployed(deployed)) {
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