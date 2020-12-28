#include <random>

#include "randomVector.hpp"

namespace Util {

    std::vector<float> randomVector(uint32_t size) {
        std::vector<float> out{};
        
        for (uint32_t i = 0; i < size; ++i) {
            out.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }

        return out;
    }

}