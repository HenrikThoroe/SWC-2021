#include "Position.hpp"

namespace Util {

    Position::Position(int x, int y) : Vector2D { x, y } {}

    bool Position::isNextTo(const Position& other) const {
        if (other == *this) {
            return false;
        }

        const int minX = x - 1;
        const int maxX = x + 1;
        const int minY = y - 1;
        const int maxY = y + 1;

        return other.x >= minX && other.x <= maxX && other.y >= minY && other.y <= maxY;
    }

    std::array<Position, 4> Position::getEdges() const {
        return {
            Position(x - 1, y),
            Position(x + 1, y),
            Position(x, y - 1),
            Position(x, y + 1)
        };
    }

    Position Position::move(const Vector2D& direction) const {
        return Position(x + direction.x, y + direction.y);
    }

    Position Position::operator + (const Vector2D& direction) const {
        return move(direction);
    }

    std::ostream& operator << (std::ostream& os, const Position& pos) {
        os << "Position { x: " << pos.x << ", y: " << pos.y << " }";
        return os;
    }

}