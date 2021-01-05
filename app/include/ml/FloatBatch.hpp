#pragma once 

#include <vector>
#include "xsimd.hpp"

namespace ML {

    using float_batch = xsimd::simd_type<float>;

    /// A batch of floats for effective SIMD computations
    struct FloatBatch {
        /// Creates a float batch by loading the data of the passed vector
        FloatBatch(const std::vector<float>& data);

        /// Copy constructor
        FloatBatch(const FloatBatch& copy);

        /// Copy constructor
        FloatBatch(const FloatBatch* copy);

        /// SIMD (AVX, SSE, NEON, ...) batches which contain as many floats as fit into a SIMD register.
        std::vector<float_batch> batches;

        /// The remaining values which do not fit into another SIMD register
        std::vector<float> remainders;

        /// The number of loaded values
        size_t size() const;

        FloatBatch operator * (const FloatBatch& rhs) const;
    };

}
