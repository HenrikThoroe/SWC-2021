#pragma once

#include <any>
#include <array>
#include <optional>

#include "MsgType.hpp"
#include "Move.hpp"

namespace App {
    
    struct Message {
        /**
         * @brief Construct a new Message
         * 
         * @param type Type of message
         * @param payload Payload of message of any type (requires casting on access)
         */
        Message(MsgType type, std::any payload);


        /// Type of message
        const MsgType type;

        /// Payload of message of any type (requires casting on access with std::any_cast<T>(i.payload))
        const std::any payload;
    };

    struct MementoMsg {
        /**
         * @brief Construct a new MementoMsg
         * 
         * @param startPiece id of startPiece
         * @param lastMove Last move played on the board
         * @param currentTurn Current turn
         */
        MementoMsg(uint8_t startPiece, std::optional<uint32_t> lastMove, uint8_t currentTurn, Model::PieceColor currentColor);


        /// Index for PieceCollection pointing at the piece that has to be played in the first round
        const uint8_t startPiece;

        /// Index for 'allPieces' cache in GameState of last move on the field
        const std::optional<uint32_t> lastMove;

        /// Current turn on the board
        const uint8_t currentTurn;

        const Model::PieceColor currentColor;
    };

    struct ResultMsg {
        /// An enum of different game end causes.
        /// @note types map to uint8_t
        enum class ResultCause: uint8_t {
            REGULAR        = 0, 
            LEFT           = 1,
            RULE_VIOLATION = 2, 
            SOFT_TIMEOUT   = 3,
            HARD_TIMEOUT   = 4

        };

        /// An enum of different game endings.
        /// @note types map to uint8_t
        enum class ResultEnd: uint8_t {
            LOSE = 0,
            DRAW = 1,
            WIN  = 2
        };

        /**
         * @brief Construct a new ResultMsg
         * 
         * @param score GameScore both players reached
         * @param end TournamentPoints both players earned
         * @param cause Game-ending causes for both players
         */
        ResultMsg(std::array<uint8_t, 2> score, std::array<ResultEnd, 2> end, std::array<ResultCause, 2> cause);


        /// An array that holds both player's current in-game score
        const std::array<uint8_t, 2>     score;

        /// An Array that holds both players tournamentPoints earned in this round
        const std::array<ResultEnd, 2>   end;

        /// An Array that holds both players game-ending causes
        const std::array<ResultCause, 2> cause;
    };
    
}
