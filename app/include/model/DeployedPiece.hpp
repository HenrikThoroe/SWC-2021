#pragma once

#include <inttypes.h>
#include <vector>
#include <iostream>

#include "Piece.hpp"
#include "Rotation.hpp"
#include "Position.hpp"
#include "color.hpp"

namespace Model {

    /// DeployedPiece contains the information to identify a piece on the board. 
    class DeployedPiece {
        public:
            /// The id of the corresenponding piece.
            const uint8_t pieceId;

            /// The origin of the piece. 
            const Util::Position origin;

            /// The rotation in which the piece has been deployed.
            const Rotation rotation;

            /// The color of the piece.
            const PieceColor color;

            /// @param initializeFields A flag indicating if `prepareOccupiedFields` and `prepareAttachPoints` should be called in the constructor. **If set to false remember to manually call these methods.**
            DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation, PieceColor color, bool initializeFields = true);
            DeployedPiece(uint8_t id, Util::Position origin, Rotation rotation, PieceColor color, std::vector<Util::Position> occupiedPositions, std::vector<Util::Position> attachPoints);
            DeployedPiece(uint8_t pieceId, PieceColor color, Rotation rotation, Util::Vector2D vectorToOrigin, Util::Position dropPosition);
            DeployedPiece(const DeployedPiece& other);
            DeployedPiece(const DeployedPiece* other);

            const std::vector<Util::Position>& getOccupiedPositions() const;

            const std::vector<Util::Position>& getAttachPoints() const;

            /// Calculates the occupied positions of the piece.
            void prepareOccupiedFields();

            /// Calculates the attach points of the piece.
            void prepareAttachPoints();

            /**
             * @brief Calculates a unique index for the piece
             * @param includeColor If false the same pieces with different colors have equal indices.
             */
            int index(bool includeColor = true) const;

            friend std::ostream& operator << (std::ostream& os, const DeployedPiece& piece);

        private:
            /// A set of all positions which are occupied by the piece.
            std::vector<Util::Position> occupiedPositions;

            /// A set of all positions where other pieces with the same color could be attached.
            std::vector<Util::Position> attachPoints;
    };

}
