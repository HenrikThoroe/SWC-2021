#pragma once

#include <vector>

#include "Message.hpp"
#include "Move.hpp"
#include "color.hpp"

namespace Logic {

    /// Class that manages the GameState and handels MoveRequests
    class GameManager {
        private:
            /// Pointer to XMLParsers`s vector of PieceColors still in the game
            const std::vector<Model::PieceColor>* const colorsInGame;

            /// Own PlayerColor
            Model::PlayerColor ownColor;

        public:
            /**
             * @brief Construct a new GameManager instance
             * 
             * @param colorsInGame Pointer to a vector of PieceColors still in the game
             */
            GameManager(const std::vector<Model::PieceColor>* const colorsInGame);

            /// No copy constructors allowed
            GameManager(GameManager* other) = delete;
            GameManager(GameManager& other) = delete;

            /**
             * @brief Set own PlayerColor
             * 
             * @param color PlayerColor to use
             */
            void setColor(const Model::PlayerColor& color);

            /**
             * @brief Update own GameState with MementoMessage send by server
             * 
             * @param memento Memento received from server
             */
            void updateWithMemento(const App::MementoMsg& memento);

            /**
             * @brief Called when the server requests a move
             * 
             * @returns Const ptr to move the logic deemed best
             */
            const Model::Move* moveRequest();
    };

}
