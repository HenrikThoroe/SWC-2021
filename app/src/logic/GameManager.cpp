#include <algorithm>
#include <optional>
#include <stdexcept>

#include "GameManager.hpp"
#include "Search.hpp"
#include "debug.hpp"

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

            while (state.getTurn() < 100 && state.getCurrentPieceColor() != memento.currentColor) {
                state.update(std::nullopt);
            }
        }
    }

    const Model::Move* GameManager::moveRequest() { 
        Search agent = Search(state, ownColor);
        SearchResult result = agent.find();

        #ifdef DEBUG
        agent.log();
        #endif

        return result.move;
    }

}
