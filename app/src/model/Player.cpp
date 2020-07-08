#include "Player.hpp"

namespace Model {

    Player::Player(PlayerColor color) : color(color) {}

    Player::Player(const Player& player) : color(player.color) {}

    Player::Player(const Player* player) : color(player->color) {}

    const std::array<PieceColor, 2>& Player::getPieceColors() const {
        return Player::pieceColors.at(uint8_t(color));
    }

    void Player::invertColor() {
        if (color == PlayerColor::BLUE) {
            color = PlayerColor::RED;
        } else {
            color = PlayerColor::BLUE;
        }
    }
}