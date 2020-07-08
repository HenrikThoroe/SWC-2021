#pragma once

#include "Vector2D.hpp"

namespace Util {

    class Position: public Vector2D {
        public:
            bool isNextTo(const Position& other) const;
    };

}