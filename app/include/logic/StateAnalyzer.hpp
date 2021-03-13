#pragma once

#include <vector>

#include "color.hpp"
#include "Rect.hpp"
#include "Player.hpp"
#include "Position.hpp"

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

            /// Finds the center of the pieces from `player`
            Util::Position getPlayerCenter(const Model::Player& player) const;

            /**
             * Calculates a value which indicates how much a color is pulled to the opposite one.
             * The closer the color is to this corner the higher the value.
             * 
             * @param color The color which should be analyzed
             * @param swapCorner If true the value is calculated as if the starting corner of the color is shifted on the y-axis
             */
            int pullFactor(const Model::PieceColor& color, bool swapCorner = false) const;

            int pushFactor(const Model::PieceColor& color) const;

            /**
             * Calculates a value which maximizes the number of own drop positions while minimizing the number of opponent drop positions
             * 
             * @param colors The colors of the maximized player
             * @param opponentColors The colors of the minimized player
             */
            int dropFactor(const std::array<Model::PieceColor, 2>& colors, const std::array<Model::PieceColor, 2>& opponentColors) const;
    };

}
