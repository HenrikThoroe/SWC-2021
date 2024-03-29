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

            /// Pointer to time the last message was received (MoveRequest)
            const std::chrono::high_resolution_clock::time_point* const lastMsgReceivedPtr;

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

            /// Number of nodes whose children were searched
            int expandedNodes;

            /// Number of searched child-nodes
            int searchedChildren;

            /// Mask that stores the colors which cannot perform further moves 
            std::bitset<4> invalidMask;
        
        public:

            Search(Model::GameState& state, const Model::PlayerColor& player, const std::chrono::high_resolution_clock::time_point* const lastMsgReceivedPtr);
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
            int alphaBeta(int alpha = INT_MIN, int beta = INT_MAX);

            /// Resets internal state to meassure performance and other data
            void reset();

            /// Calculates the elapsed time since last `reset` call
            std::chrono::high_resolution_clock::duration getElpasedTime() const;

            /// Sort the given moves by principal variation
            void sortMoves(std::vector<const Model::Move*>& moves, const Model::Move* hashMove) const;

            /// Returns `true` if the current session timed out
            bool timedOut() const;

            /**
             * @brief Reads an entry from the transposition table for the current state
             * 
             * @param exact Will be assigned the exact value of the node if available
             * @param alpha Will be assigned the upper bound of the node if available
             * @param beta Will be assigned the lower bound of the node if available
             * @param bestMove The best move found at this node or nullptr if none was found
             * @param depth The current search depth to filter hits with lower depth
             * @returns `true` if an entry is found
             */
            bool fetchEntry(int& exact, int& alpha, int& beta, const Model::Move*& bestMove, int depth);

            /**
             * @brief Writes an entry for the current state to the transposition table
             * 
             * @param score The evaluation of the state
             * @param depth The depth to which the state was evaluated
             * @param type The type of the score. LOWER_BOUND if alpha cutoff, UPPER_BOUND if beta cutoff, otherwise EXACT
             * @param bestMove The best move found at this node or nullptr if none was found
             */
            void setEntry(int score, int depth, const TTEntryType& type, const Model::Move* bestMove);

            /// Adds the passed move to the killer table 
            void insertKiller(const Model::Move* move);

        private:

            /**
             * @brief Prepares a search iteration by fetching alpha, beta or the exact score from the transposition table and handles terminal nodes
             * 
             * @param alpha A refernce to alpha which could be changed if a value is available in the transposition table
             * @param beta A refernce to beta which could be changed if a value is available in the transposition table
             * @param depth The current search depth required to terminate search if neccessary
             * @param moves A refernce to a moves vector where all available moves will be assigned and sorted
             * @param nodeValue The exact value of the node if it is a terminal node or the search depth reaches zero
             * @param didInvalidate A boolean value required for `finishSearch` which indicates if the current color invalidates at the present state
             * @returns True if the search should be terminated at this node
             */
            bool prepareSearch(int& alpha, int& beta, int depth, std::vector<const Model::Move*>& moves, int& nodeValue, bool& didInvalidate);

            /**
             * @brief Performs required tasks when a search iteration has been finished
             * 
             * @param alpha The new alpha value 
             * @param beta The new beta value
             * @param score The score of the searched node
             * @param depth The depth of the searched node 
             * @param didInvalidate A flag to decide whether the current color is valid again or not
             */
            void finishSearch(int alpha, int beta, int score, int depth, const Model::Move* bestMove, bool didInvalidate);

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
