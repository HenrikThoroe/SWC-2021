#include "Position.hpp"

namespace Util {

    bool Position::isNextTo(const Position& other) const {
        const int minX = x - 1;
        const int maxX = x + 1;
        const int minY = y - 1;
        const int maxY = y + 1;

        return other.x >= minX && other.x <= maxX && other.y >= minY && other.y <= maxY;
    }

}