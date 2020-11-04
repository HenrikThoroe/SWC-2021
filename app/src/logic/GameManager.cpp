#include "GameManager.hpp"

namespace Logic {
    
    GameManager::GameManager(const std::vector<Model::PieceColor>* const colorsInGame) : colorsInGame(colorsInGame) {}

    void GameManager::setColor(const Model::PlayerColor& color) {
        ownColor = color;
    }

    void GameManager::updateWithMemento(const App::MementoMsg& memento) {
        if (state.initialPiece == -1) {
            state.initialPiece = static_cast<int>(memento.startPiece);
        }

        if (memento.currentTurn > 0) {
            state.update(memento.lastMove);

            /// TODO: Handle possibility that one or more colors are skipped by the server
        }


    }

    const Model::Move* GameManager::moveRequest() {
        lastTurnWithActivity = state.getTurn();
        
        std::vector<const Model::Move*> moves;
        state.assignPossibleMoves(moves);

        if (moves.size() == 0) {
            std::cout << "Skiping" << std::endl;
            return nullptr;
        }

        const Model::Move* move = moves[rand() % moves.size()];

        std::cout << *move << std::endl;

        return move;
    }

}
