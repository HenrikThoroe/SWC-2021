#pragma once

#include <iostream>

#include "Vector2D.hpp"

namespace Util {

    class Position: public Vector2D {
        public:
            Position(int x, int y);

            bool isNextTo(const Position& other) const;

            Position move(const Vector2D& direction) const;

            Position operator + (const Vector2D& direction) const;

            friend std::ostream& operator << (std::ostream& os, const Position& pos);
    };

}