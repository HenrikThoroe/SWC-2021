#pragma once

#include <iostream>
#include <array>

#include "Vector2D.hpp"

namespace Util {

    class Position: public Vector2D {
        public:
            Position();

            Position(int8_t x, int8_t y);

            bool isNextTo(const Position& other) const;

            std::array<Position, 4> getEdges() const;

            std::array<Position, 4> getCorners() const;

            Position move(const Vector2D& direction) const;

            Position operator + (const Vector2D& direction) const;

            Position operator - (const Vector2D& direction) const;

            friend std::ostream& operator << (std::ostream& os, const Position& pos);
    };

}
