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

namespace Model {

    class GameState {
        public:

            const int initialPiece;

        private:

            struct MoveCacheEntry {
                std::vector<const Move*> value;
                uint32_t accesses;
                uint8_t turn;
            };

            /// Collection of all available players.
            const std::array<Player, 2> players;

            /// A stack (first-in last-out) which tracks the performed moves.
            std::stack<std::optional<DeployedPiece>> performedMoves {};

            /// A cache to improve move calculation speed.
            tsl::robin_map<uint64_t, MoveCacheEntry> movesCache;

            /// A board instance which stores the state of the deloyed pieces.
            Board board;

            /// The current turn. 
            uint8_t turn;

            /// A collection of all remaining piece shapes stored as an array of their IDs for each color.
            std::array<std::array<uint8_t, 21>, 4> availablePieces {};

            /// A cache which stores stores all deployed pieces possible on the board.
            /// @note Size: 268,800 * 84 Bytes = 22,579,200 Byte ~= 22 Megabyte
            std::vector<DeployedPiece> allPieces {};

            /// A bitset which indicates which piece cannot be deployed on the state. 
            /// Each bit is logically connected to the DeployedPiece in `allPieces` at the same index. 
            std::bitset<268800> undeployablePieces {};

            /// A history of `undeployablePieces` to revert moves.
            std::stack<std::bitset<268800>> undeployablePiecesHistory {};

            /// A set of random 64 bit numbers to implement zobrist hashing. Size: ~2MB
            std::array<uint64_t, 268800> hashpool {};

            /// The current hash value of the game state.
            uint64_t hashValue = 0;

            /// Calculates a unique index for the piece to access it in `allPieces` / `undeployablePieces`. 
            int createIndex(const DeployedPiece* piece) const;

        public:
            GameState(int initialPiece);
            GameState(GameState* other) = delete;
            GameState(GameState& other) = delete;

            /// Returns the current turn.
            const uint8_t& getTurn() const;

            /// Returns the player which is eligible to perform the next move.
            const Player& getCurrentPlayer() const;

            /// Returns the color which may be deployed next.
            const PieceColor& getCurrentPieceColor() const;

            /// Finds and returns the possible moves on the current game board.
            std::vector<const Move*> getPossibleMoves();

            /// Fills the passed vector with the moves possible on the current game state.
            void assignPossibleMoves(std::vector<const Move*>& moves);

            /// Performs the given move on the board. If nullptr is passed, the move will be skipped according to the official game rules.
            void performMove(const Move* move);

            /// Reverts the last performed move.
            void revertLastMove();

            /// Checks whether the specified piece can be bedployed on the board.
            bool canBeDeployed(const DeployedPiece& piece);

            /// Checks whether the specified piece can be bedployed on the board.
            bool canBeDeployed(const DeployedPiece* piece);

            /// Hashes the current state.
            uint64_t hash() const;

            /// Creates a unique hash for the game state which has no collisions.
            std::bitset<808> uniqueHash() const;

            /// Evaluates the current state.
            int evaluate() const;

            void freeMemory(float percent = 0.5);

            friend std::ostream& operator << (std::ostream& os, const GameState& state);
    };

}