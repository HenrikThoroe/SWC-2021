#pragma once

#include <chrono>

#include "Move.hpp"
#include "GameState.hpp"
#include "TranspositionTable.hpp"

namespace Logic {

    /// A structure representing the result of a search
    struct SearchResult {
        SearchResult(const Model::Move* move, const int score);

        /// The best move found by the search algorithm
        const Model::Move* move;

        /// The associated score of the found move.
        const int score;
    };

    /**
     * The base class for finding the best move. 
     * It provides the foundation for more advanced search algorithms.
     * By default Alpha Beta search is used.
     */
    class Search {
        private:

            /// Internal high resolution clock
            std::chrono::high_resolution_clock clock;

            /// The start time of the most recent search. Call `reset` to initiate.
            std::chrono::high_resolution_clock::time_point startTime;

            /// A table which stores already explored states to speed up searching
            TranspositionTable table;

            /// A counter for table hits for search statistics
            int tableHits;

            /// Table to store killer moves, which caused Beta cutoffs
            std::array<std::vector<const Model::Move*>, 100> killerTable {};

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

            /// The last found score
            int lastScore;

            /// Mask that stores the colors which cannot perform further moves 
            std::bitset<4> invalidMask;
        
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

            /// Sets the colors which are out of game
            void setInvalidColors(const std::vector<Model::PieceColor>* const valid);

            /// Prepares cache memory for reuse.
            void clean();

        protected:

            /**
             * Default search algorithm
             * @return The score of the best move
             */
            int alphaBeta();

            /// Resets internal state to meassure performance and other data
            void reset();

            /// Calculates the elapsed time since last `reset` call
            std::chrono::high_resolution_clock::duration getElpasedTime() const;

            /// Sort the given moves by principal variation
            void sortMoves(std::vector<const Model::Move*>& moves) const;

            /// Returns `true` if the current session timed out
            bool timedOut() const;

            /**
             * @brief Reads an entry from the transposition table for the current state
             * @param exact Will be assigned the exact value of the node if available
             * @param alpha Will be assigned the upper bound of the node if available
             * @param beta Will be assigned the lower bound of the node if available
             * @param depth The current search depth to filter hits with lower depth
             * @returns `true` if an entry is found
             */
            bool fetchEntry(int& exact, int& alpha, int& beta, int depth);

            /**
             * @brief Writes an entry for the current state to the transposition table
             * @param score The evaluation of the state
             * @param depth The depth to which the state was evaluated
             * @param type The type of the score. LOWER_BOUND if alpha cutoff, UPPER_BOUND if beta cutoff, otherwise EXACT
             */
            void setEntry(int score, int depth, const TTEntryType& type);

            void insertKiller(const Model::Move* move);

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
