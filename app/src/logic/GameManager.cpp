#include <algorithm>
#include <optional>
#include <stdexcept>

#include "GameManager.hpp"
#include "debug.hpp"
#include "stringTools.hpp"
#include "Process.hpp"

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
        const Util::Process proc = Util::Process();

        std::cout << "Score: ";

        if (ownColor == Model::PlayerColor::BLUE) {
            std::cout << Util::Print::Text::bold(std::to_string(message.score[0])) << " : " << std::to_string(message.score[1]);
        } else {
            std::cout << std::to_string(message.score[0]) << " : " << Util::Print::Text::bold(std::to_string(message.score[1]));
        }

        std::cout << '\n' << state << '\n' << '\n';

        proc.printSystemStatus();
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

            agent.setInvalidColors(this->colorsInGame);

            #ifdef DEBUG
            std::cout << Util::Print::Text::bold("Colors in Game: ");

            for (const Model::PieceColor& color : *colorsInGame) {
                std::cout << color << " ";
            }

            std::cout << '\n' << Util::Print::Text::bold("Available Moves: ") << state.getPossibleMoves().size() << std::endl;
            #endif
        }
    }

    const Model::Move* GameManager::moveRequest() { 
        SearchResult result = agent.find();
        const Util::Process proc = Util::Process();
        const double usedMemory = static_cast<double>(proc.virtualMemory()) / 1'000'000;

        #ifdef DEBUG
        agent.log();
        #endif

        if (usedMemory > 1100) {
            const double percentage = (usedMemory - 1100) / 10000 * 15; // 15% per 100 MB > 1100 MB => 1400MB used -> 200 > 1100 -> 30% of cache is freed for reuse
            state.freeMemory(percentage);
        } else {
            state.freeMemory(0);
        }

        agent.clean();

        return result.move;
    }

}
