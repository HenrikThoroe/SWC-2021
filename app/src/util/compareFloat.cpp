#include <inttypes.h>

#include "compareFloat.hpp"

namespace Util {

    bool compareFloat(float a, float b, float epsilon) {
        if (a == b) {
            return true;
        }

        if (fabsf(a - b) < std::numeric_limits<float>::epsilon()) {
            return true;
        }

        return fabs(a - b) < epsilon;
    }

}
