#include <inttypes.h>

#include "compareFloat.hpp"

namespace Util {

    bool compareFloat(float a, float b, int precision) {
        return static_cast<int64_t>(a * powf(10, precision)) == static_cast<int64_t>(b * powf(10, precision));
    }

}
