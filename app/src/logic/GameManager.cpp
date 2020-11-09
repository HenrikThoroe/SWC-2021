#include <algorithm>
#include <optional>
#include <stdexcept>

#include "GameManager.hpp"

namespace Logic {
    
    GameManager::GameManager(const std::vector<Model::PieceColor>* const colorsInGame) : colorsInGame(colorsInGame) {}

    void GameManager::setColor(const Model::PlayerColor& color) {
        ownColor = color;
    }

    const Model::PlayerColor& GameManager::getPlayerColor() const {
        return ownColor;
    }

    void GameManager::updateWithMemento(const App::MementoMsg& memento) {
        if (state.initialPiece == -1) {
            state.initialPiece = static_cast<int>(memento.startPiece);
        }

        if (memento.currentTurn > 0) {
            state.update(memento.lastMove);

            while (state.getTurn() < 100 && std::find(colorsInGame->begin(), colorsInGame->end(), state.getCurrentPieceColor()) == colorsInGame->end()) {
                state.update(std::nullopt);
            }
        }


    }

    const Model::Move* GameManager::moveRequest() {  
        std::vector<const Model::Move*> moves;
        state.assignPossibleMoves(moves);

        if (moves.size() == 0) {
            throw std::runtime_error("No moves found. This should not happen because the server only requests a move if possible.");
        }

        return moves[rand() % moves.size()];
    }

}
