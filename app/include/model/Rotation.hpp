#pragma once

#include <inttypes.h>

namespace Model {

    /// An enum describing the rotation of a piece in radians.
    /// @note Rotation maps to uint8_t
    enum class Rotation: uint8_t {
        ZERO, ONEHALFPI, PI, THREEHALFPI
    };

}