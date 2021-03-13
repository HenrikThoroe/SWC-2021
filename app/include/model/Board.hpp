#pragma once

#include <array>
#include <inttypes.h>
#include <iostream>

#include "Move.hpp"
#include "DeployedPiece.hpp"

namespace Model {

    /// A collection of statistics about the current board state for a specific color
    struct BoardStatistics {

        BoardStatistics();
        BoardStatistics(const PieceColor& color);
        BoardStatistics(BoardStatistics* other) = delete;
        BoardStatistics(BoardStatistics& other) = delete;

        /// The statistic is created for this color
        PieceColor color;

        /**
         * A value which indicates how much the color is pulled to each corner.
         * Starting at (0, 0) <-> top left and rotating clockwise
         */
        std::array<int, 4> pullFactor;

        /// The number of free corners 
        int freeCorners;

        /// The number of corners where a friendly color is blocking. Does not include the same color
        int friendlyBlockedCorners;

        /// The number of corners where the opponent is blocking
        int opponentBlockedCorners;

        /// The number of edges which are shared with another color
        int sharedEdges;

        /// The number of edges which are shared with the other team color
        int friendlySharedEdges;

        /// The number of edges which are shared with an opponent color
        int opponentSharedEdges;

        /// The number of available drop positions
        int dropPositions;

        /**
         * The number of drop posotions sorted by their estimated value.
         * The index indicates how many fields around the field are free.
         * Positions outside of the board count as not free.
         * Each entry represents the number of drop positions with specific amount of free neighbour fields.
         */
        std::array<int, 8> ratedDropPositions;

        void reset();
    };

    class Board {
        public:
            /// A shorthand for a two dimensional array of the size 20x20 (BoardSize x BoardSize), which stores the color of the field.
            typedef std::array<std::array<PieceColor, 20>, 20> FieldSet;

            /// A shorthand for a two dimensional array of the size 20x20 (BoardSize x BoardSize), which stores one byte per field.
            typedef std::array<std::array<int8_t, 20>, 20> RawFieldSet;

            Board();
            Board(Board* other) = delete;
            Board(Board& other) = delete;

            /// Deploys a piece on the current board instance.
            void dropPiece(const DeployedPiece& piece);

            /// Removes a piece from the current board instance.
            void removePiece(const DeployedPiece& piece);

            /// Reads the piece color at the given position.
            const PieceColor& at(const Util::Position& position) const;

            /// Reads the piece color at the given coordinates.
            const PieceColor& at(int x, int y) const;

            /// Reads the piece color at the given coordinates. No validation checks are performed.
            const PieceColor& at_unsafe(int x, int y) const;

            /// Calculates the available drop positions for the specified color.
            std::vector<Util::Position> getDropPositions(const PieceColor& color) const;

            /**
             * Estimates the number of available drop positions for two colors. It has not to be the exact value
             * 
             * @param firstColor The first color whose drop positions should be counted
             * @param secondColor The second color whose drop positions should be counted
             * @returns The estimated number of drop positions
             */
            int estimateDropPositions(const PieceColor& firstColor, const PieceColor& secondColor) const;

            /// Checks if a piece of the passed color can be droped at the given position.
            bool canDrop(const PieceColor& color, const Util::Position& position) const;

            /// Checks if a piece of the passed color can be droped at the given coordinates.
            bool canDrop(const PieceColor& color, int x, int y) const;

            /// Forces the specified position to be a drop zone for the passed color.
            void makeDropPosition(const Util::Position& position, const PieceColor& color);

            const std::array<BoardStatistics, 4>& getStatistics() const;

            friend std::ostream& operator << (std::ostream& os, const Board& board);

            const PieceColor& operator [] (const Util::Position& position) const;

        private:
            /// A 20x20 array which stores the piece color for each position of the board.
            FieldSet fields {};

            /// An array which stores four representations of the board. 
            /// Each field of the board is described by an uint8_t value which indicates the number of possible attach points.
            /// If the value is 0 no piece can be attached to this position.
            /// @note 'dropPositions' should be indexed with instances of 'PieceColor' - 1.
            std::array<RawFieldSet, 4> dropPositions {};

            mutable std::array<BoardStatistics, 4> statistics;

            std::array<Util::Position, 400> positions{};

            std::array<std::vector<const Util::Position*>, 400> neighbours;

            std::array<std::vector<const Util::Position*>, 400> corners;

            int getIndex(int x, int y) const;

            const std::vector<const Util::Position&>& getNeighbours(int x, int y) const;
    };

}
