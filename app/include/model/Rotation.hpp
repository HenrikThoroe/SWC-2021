#pragma once

#include <inttypes.h>

namespace Model {

    /// An enum describing the rotation of a piece in radians. 
    /// @note Rotation maps to uint8_t
    enum class Rotation: uint8_t {
        ZERO = 0, 
        ONEHALFPI = 1,
        PI = 2, 
        THREEHALFPI = 3,
        ZERO_FLIPPED = 4, 
        ONEHALFPI_FLIPPED = 5,
        PI_FLIPPED = 6, 
        THREEHALFPI_FLIPPED = 7
    };

}