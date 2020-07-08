#pragma once 

#include "Vector2D.hpp"
#include <inttypes.h>
#include <vector>
#include <array>
#include <tuple>

namespace Model {

    struct Piece {
        typedef std::vector<Util::Vector2D> Shape;
        typedef std::array<Util::Vector2D, 2> AttachPoint;
        typedef std::vector<AttachPoint> AttachPoints;
        typedef std::tuple<Shape, AttachPoints> Rotation;

        uint8_t id;
        std::array<Rotation, 4> rotations;
    };

}