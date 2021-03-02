#pragma once 

#include <inttypes.h>
#include <stack>
#include <bitset>
#include <optional>
#include "robin_map.hpp"

#include "Board.hpp"
#include "Player.hpp"
#include "DeployedPiece.hpp"
#include "Piece.hpp"
#include "constants.hpp"

namespace Model {

    class GameState {
        public:

            int initialPiece;

        private:

            struct MoveCacheEntry {
                std::vector<const Move*> value;
                uint32_t accesses;
                uint8_t turn;
            };

            /// Collection of all available players.
            const std::array<Player, 2> players;

            /// A cache to improve move calculation speed.
            tsl::robin_map<uint64_t, MoveCacheEntry> movesCache;

            /// A board instance which stores the state of the deloyed pieces.
            Board board;

            /// The current turn. 
            uint8_t turn;

            /// A collection of all remaining piece shapes stored as an array of their IDs for each color.
            std::array<std::array<uint8_t, Constants::PIECE_SHAPES>, 4> availablePieces {};

            /// A history for each color which contains the order in which the pieces have been deployed.
            std::array<std::stack<uint8_t>, 4> pushHistory;

            /// A cache which stores stores all deployed pieces possible on the board.
            /// @note Size: 268,800 * 84 Bytes = 22,579,200 Byte ~= 22 Megabyte
            std::vector<DeployedPiece> allPieces {};

            /// A set of random 64 bit numbers to implement zobrist hashing. Size: ~2MB
            std::array<uint64_t, Constants::PIECE_VARIANTS> hashpool {};

            /// The current hash value of the game state.
            uint64_t hashValue = 0;

            /// Calculates a unique index for the piece to access it in `allPieces` 
            int createIndex(const DeployedPiece* piece, bool includeColor = true) const;

        public:
            GameState(int initialPiece);
            GameState(GameState* other) = delete;
            GameState(GameState& other) = delete;

            /**
             * @brief Updates the state with the given move.
             * @param move The id of the move, which should be performed, or nullopt if the move should be skipped.
             */
            void update(std::optional<uint32_t> move);

            /// Returns the current turn.
            const uint8_t& getTurn() const;

            /// Returns the player which is eligible to perform the next move.
            const Player& getCurrentPlayer() const;

            /// Returns the color which may be deployed next.
            const PieceColor& getCurrentPieceColor() const;

            /**
             * Returns the player who commited the last move.
             * @throw Throws an std::runtime_exception if the turn is 0.
             */
            const Player& getLastPlayer() const;

            /**
             * Returns the piece color of the last move even if it has been skipped.
             * @throw Throws an std::runtime_exception if the turn is 0.
             */
            const PieceColor& getLastPieceColor() const;

            /// Finds and returns the possible moves on the current game board.
            std::vector<const Move*> getPossibleMoves();

            /// Fills the passed vector with the moves possible on the current game state.
            void assignPossibleMoves(std::vector<const Move*>& moves);

            /// Performs the given move on the board. If nullptr is passed, the move will be skipped according to the official game rules.
            void performMove(const Move* move);

            /// Reverts the given move on the board. This is the inverse of performMove.
            void revertMove(const Move* move);

            /// Checks whether the specified piece can be bedployed on the board.
            bool canBeDeployed(const DeployedPiece& piece);

            /// Checks whether the specified piece can be bedployed on the board.
            bool canBeDeployed(const DeployedPiece* piece);

            /// Hashes the current state.
            uint64_t hash() const;

            /// Creates a unique hash for the game state which has no collisions.
            std::bitset<808> uniqueHash() const;

            /**
             * @brief Evaluates the current state for the assigned player.
             * @param player The player whose score should be calculated
             * @param invalidColors A pointer to a bitset which tells the function if any color is invalid
             */
            int evaluate(const PlayerColor& player, const std::bitset<4>* invalidColors = nullptr) const;

            /// Returns whether performing a move on the current state would be illegal.
            bool isGameOver() const;

            void freeMemory(float percent = 0.5);

            friend std::ostream& operator << (std::ostream& os, const GameState& state);
    };

}
