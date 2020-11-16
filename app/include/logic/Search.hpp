#pragma once

#include <chrono>

#include "Move.hpp"
#include "GameState.hpp"

namespace Logic {

    /// A structure representing the result of a search
    struct SearchResult {
        SearchResult(const Model::Move* move, const int score);

        /// The best move found by the search algorythm
        const Model::Move* move;

        /// The associated score of the found move.
        const int score;
    };

    /**
     * The base class for finding the best move. 
     * It provides the foundation for more advanced search algorythms.
     * By default Alpha Beta search is used.
     */
    class Search {
        private:

            /// Internal high resolution clock
            std::chrono::high_resolution_clock clock;

            /// The start time of the most recent search. Call `reset` to initiate.
            std::chrono::high_resolution_clock::time_point startTime;

        protected:

            /// A reference to the used game state
            Model::GameState& state;

            /// The player whose result should be maximized
            const Model::PlayerColor& player;

            /// The move which is best for the player
            const Model::Move* selectedMove;

            /// The maximum search depth
            int maxDepth;

            /// Number of visited nodes / game states.
            int searchedNodes;

            /// The number of alpha cutoffs. Used to create detailed statistics.
            int alphaCutoffs;

            /// The number of beta cutoffs. Used to create detailed statistics.
            int betaCutoffs;
        
        public:

            Search(Model::GameState& state, const Model::PlayerColor& player);
            Search(Search& other) = delete;
            Search(Search* other) = delete;

            /**
             * Finds and returns the best possible move. 
             * This method should be overridden by subclasses to implement different algorithms.
             * @return A `SearchResult` object containing the best move and it's score
             */
            virtual SearchResult find();

            /// Prints the stats of the most recent search to cout. Should only be used when #DEBUG is set
            void log() const;

        protected:

            /**
             * Default search algorythm
             * @return The score of the best move
             */
            int alphaBeta();

            /// Resets internal state to meassure performance and other data
            void reset();

            /// Calculates the elapsed time since last `reset` call
            std::chrono::high_resolution_clock::duration getElpasedTime() const;

            /// Sort the given moves by principal variation
            void sortMoves(std::vector<const Model::Move*>& moves) const;

        private:

            /**
             * Finds and returns the best possible move on the current game state for the opponent, which is the worst move for `player`
             * @returns The score of the evaluated state
             */
            int min(int alpha, int beta, int depth);

            /**
             * Finds and returns the best possible move on the current game state for `player`
             * @returns The score of the evaluated state
             */
            int max(int alpha, int beta, int depth);

    };

}
