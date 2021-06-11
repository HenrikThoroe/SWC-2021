#pragma once

#include <vector>

#include "color.hpp"
#include "Rect.hpp"
#include "Player.hpp"
#include "Position.hpp"
#include "Board.hpp"

// Forward declare GameState to prevent cross-includes
namespace Model {
    class GameState;
}

namespace Logic {

    /// A class which is responsible to do non-basic state evaluation
    class StateAnalyzer {
        private: 
        
            /// Pointer to GameState object which should be analyzed
            const Model::GameState* gameState;

        public: 

            StateAnalyzer(const Model::GameState* gameState);
            StateAnalyzer(StateAnalyzer* other) = delete;
            StateAnalyzer(StateAnalyzer& other) = delete;

            /**
             * Evaluates the game state based on a specific strategy
             * 
             * @param colors The colors of the maximized player
             * @param opponentColors The colors of the minimized player
             */
            int strategyPoints(const std::array<Model::PieceColor, 2>& colors, const std::array<Model::PieceColor, 2>& opponentColors) const;
            
        private:

            /// Finds the bounds of `color` on the game board
            Util::Rect getBoundingRect(const Model::PieceColor& color) const;

            /// Returns the area of the deployed pieces of `player`
            Util::Rect getPlayerArea(const Model::Player& player) const; 

            /**
             * Turn independent basic strategie points. Covers general aspects like drop positions, blocked corners and piece spread.
             * 
             * @param stats The statistics of the board
             * @param colorIdx The indecies of the player colors in stats
             * @param opponentColorIdx The indecies of the opponent colors in stats
             */
            int basicStrategie(const std::array<Model::BoardStatistics, 4>& stats, const std::array<int, 2> colorIdx, const std::array<int, 2> opponentColorIdx) const;
    };

}
