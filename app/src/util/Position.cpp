#include <unordered_map>

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

    const std::array<Position, 4>& Position::getEdges() const {
        static std::unordered_map<int, std::array<Position, 4>> cache {};
        int key = x + x * y;

        if (cache.find(key) == cache.end()) {
            cache.insert({ 
                key, {
                    Position(x - 1, y), 
                    Position(x + 1, y),
                    Position(x, y - 1), 
                    Position(x, y + 1)
                } 
            });
        }

        return cache.at(key);
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
        os << "Position { x: " << pos.x << ", y: " << pos.y << " }";
        return os;
    }

}