#pragma once

#include <iostream>
#include <array>

#include "Vector2D.hpp"

namespace Util {

    class Position: public Vector2D {
        public:
            Position(int x, int y);

            bool isNextTo(const Position& other) const;

            std::array<Position, 4> getEdges() const;

            Position move(const Vector2D& direction) const;

            Position operator + (const Vector2D& direction) const;

            friend std::ostream& operator << (std::ostream& os, const Position& pos);
    };

}