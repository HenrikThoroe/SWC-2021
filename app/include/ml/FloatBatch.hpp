#pragma once 

#include <vector>
#include "xsimd.hpp"

namespace ML {

    using float_batch = xsimd::simd_type<float>;

    struct FloatBatch {
        FloatBatch(const std::vector<float>& data);

        std::vector<float_batch> batches;
        std::vector<float> remainders;

        size_t size() const;

        FloatBatch operator * (const FloatBatch& rhs) const;
    };

}
