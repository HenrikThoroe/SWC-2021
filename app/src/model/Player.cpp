#include "Player.hpp"

namespace Model {

    Player::Player(PlayerColor color) : color(color) {}

    Player::Player(const Player& player) : color(player.color) {}

    Player::Player(const Player* player) : color(player->color) {}

    const std::array<std::array<PieceColor, 2>, 2> Player::pieceColors = {{
        { PieceColor::BLUE, PieceColor::RED },
        { PieceColor::YELLOW, PieceColor::GREEN }
    }};

    const std::array<PieceColor, 2>& Player::getPieceColors() const {
        return Player::pieceColors.at(static_cast<uint8_t>(color));
    }

    void Player::invertColor() {
        if (color == PlayerColor::BLUE) {
            color = PlayerColor::RED;
        } else {
            color = PlayerColor::BLUE;
        }
    }
}