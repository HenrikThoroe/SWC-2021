#pragma once

#include <vector>
#include <mutex>

#include "Message.hpp"
#include "Search.hpp"
#include "Move.hpp"
#include "color.hpp"
#include "GameState.hpp"

namespace Logic {

    /// Class that manages the GameState and handels MoveRequests
    class GameManager {
        private:
            /// Pointer to XMLParsers`s vector of PieceColors still in the game
            const std::vector<Model::PieceColor>* const colorsInGame;

            /// Own PlayerColor
            Model::PlayerColor ownColor;

            /// Mutex to prevent data races when freeing memory in background
            std::mutex moveRequestGuard {};
            
            Model::GameState state = Model::GameState(-1);

            Search agent;

        public:
            /**
             * @brief Construct a new GameManager instance
             * 
             * @param colorsInGame Pointer to a vector of PieceColors still in the game
             * @param lastMsgReceivedPtr Pointer to time the last message was received (MoveRequest)
             */
            GameManager(const std::vector<Model::PieceColor>* const colorsInGame, const std::chrono::high_resolution_clock::time_point* const lastMsgReceivedPtr);

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
             * @brief Update own GameState with MementoMessage sent by server
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

            const Model::PlayerColor& getPlayerColor() const;

            void handleResults(const App::ResultMsg& message) const;

            /**
             * @brief Get a const reference to the encapsulated GameState
             * 
             * @returns Managed GameState
             */
            const Model::GameState& getManagedState() const;
    };

}
