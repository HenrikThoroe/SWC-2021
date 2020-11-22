#include <algorithm>
#include <optional>
#include <stdexcept>

#include "GameManager.hpp"
#include "debug.hpp"
#include "stringTools.hpp"

namespace Logic {
    
    GameManager::GameManager(const std::vector<Model::PieceColor>* const colorsInGame) : colorsInGame(colorsInGame), agent(state, ownColor) {}

    void GameManager::setColor(const Model::PlayerColor& color) {
        ownColor = color;
    }

    const Model::PlayerColor& GameManager::getPlayerColor() const {
        return ownColor;
    }

    void GameManager::handleResults(const App::ResultMsg& message) const {
        #ifdef DEBUG
        std::cout << "Score: ";

        if (ownColor == Model::PlayerColor::BLUE) {
            std::cout << Util::Print::Text::bold(std::to_string(message.score[0])) << " : " << std::to_string(message.score[1]);
        } else {
            std::cout << std::to_string(message.score[0]) << " : " << Util::Print::Text::bold(std::to_string(message.score[1]));
        }

        std::cout << std::endl << state << std::endl;
        #endif
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

            agent.setInvalidColors(4 - colorsInGame->size());
        }
    }

    const Model::Move* GameManager::moveRequest() { 
        SearchResult result = agent.find();

        #ifdef DEBUG
        agent.log();
        #endif

        return result.move;
    }

}
