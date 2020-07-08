#pragma once 

#include "color.hpp"
#include <array>

namespace Model {

    /// Player stores the information which identifies a player. This includes the player's color and the color of it's pieces.
    class Player {
        public:
            /// The color of the player. This value is assigned by the game server.
            PlayerColor color;

            Player(PlayerColor color);

            Player(const Player&);

            Player(const Player*);

            /// Inverts the player's color to it's logical opposite. Red -> Blue; Blue -> Red;
            void invertColor();

            std::array<PieceColor, 2>& getPieceColors() const;

        private:
            /// The available piece colors for each player. 
            /// The player color works as index for acceessing a array which contains the assigned colors.
            static std::array<std::array<PieceColor, 2>, 2> pieceColors;
    };

}