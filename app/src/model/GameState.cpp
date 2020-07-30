#include <stdexcept>

#include "GameState.hpp"

namespace Model {

    GameState::GameState() : turn(0), players({ Player(PlayerColor::RED), Player(PlayerColor::BLUE) }) {
        std::fill(availablePieces.begin(), availablePieces.end(), 1);
    }

    const uint8_t& GameState::getTurn() const {
        return turn;
    }

    const Player& GameState::getCurrentPlayer() const {
        return players[turn % 2];
    }

    const PieceColor& GameState::getCurrentPieceColor() const {
        const int idx = turn % 4;
        return getCurrentPlayer().getPieceColors().at(idx > 1 ? idx - 2 : idx);
    }

    void GameState::performMove(const Move& move) {
        availablePieces[int(move.color) - 1][move.pieceId] -= 1;
        board.dropPiece(move);
        performedMoves.push(move);
        turn += 1;
    }

    void GameState::revertLastMove() {
        DeployedPiece& piece = performedMoves.top();

        availablePieces[int(piece.color) - 1][piece.pieceId] += 1;
        board.removePiece(piece);
        performedMoves.pop();
        turn -= 1;
    }

    const std::vector<Move>& GameState::getPossibleMoves() const {
        throw std::runtime_error("Not Implemented");
    }

    uint64_t GameState::hash() const {
        throw std::runtime_error("Not Implemented");
    }

    int GameState::evaluate() const {
        throw std::runtime_error("Not Implemented");
    }

}