#include <unordered_map>
#include <inttypes.h>

#include "Position.hpp"

namespace Util {

    Position::Position(int8_t x, int8_t y) : Vector2D { x, y } {}

    bool Position::isNextTo(const Position& other) const {
        if (other == *this) {
            return false;
        }

        const int8_t minX = x - 1;
        const int8_t maxX = x + 1;
        const int8_t minY = y - 1;
        const int8_t maxY = y + 1;

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

    Position Position::operator - (const Vector2D& direction) const {
        return move(-direction);
    }

    std::ostream& operator << (std::ostream& os, const Position& pos) {
        os << "Position { x: " << static_cast<int>(pos.x) << ", y: " << static_cast<int>(pos.y) << " }";
        return os;
    }

}