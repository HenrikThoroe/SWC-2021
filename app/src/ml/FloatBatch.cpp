#include "FloatBatch.hpp"

namespace ML {

    FloatBatch::FloatBatch(const std::vector<float>& data) : batches({}), remainders({}) {
        std::vector<float, XSIMD_DEFAULT_ALLOCATOR(float)> aligned{};
        aligned.insert(aligned.begin(), data.begin(), data.end());
        size_t increment = float_batch::size;
        size_t vectorizableSize = aligned.size() - aligned.size() % increment;

        batches.resize(vectorizableSize / increment);

        for (int i = 0; i < vectorizableSize; i += increment) {
            batches[i / increment] = xsimd::load_aligned(&aligned[i]);
        }

        for (int i = vectorizableSize; i < aligned.size(); ++i) {
            remainders.push_back(aligned[i]);
        }
    }

    size_t FloatBatch::size() const {
        return batches.size() * float_batch::size + remainders.size();
    }

    FloatBatch FloatBatch::operator * (const FloatBatch& rhs) const {
        FloatBatch out = FloatBatch({});

        for (size_t i = 0; i < batches.size(); ++i) {
            out.batches.push_back(batches[i] * rhs.batches[i]);
        }

        for (size_t i = 0; i < remainders.size(); ++i) {
            out.remainders.push_back(remainders[i] * rhs.remainders[i]);
        }

        return out;
    }

}
