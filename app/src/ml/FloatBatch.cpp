#include "FloatBatch.hpp"

namespace ML {

    FloatBatch::FloatBatch(const std::vector<float>& data) : batches({}), remainders({}) {
        size_t increment = float_batch::size;
        size_t vectorizableSize = data.size() - data.size() % increment;

        batches.resize(vectorizableSize / increment);

        for (int i = 0; i < vectorizableSize; i += increment) {
            batches[i / increment] = xsimd::load_unaligned(&data[i]);
        }

        for (int i = vectorizableSize; i < data.size(); ++i) {
            remainders.push_back(data[i]);
        }
    }

    FloatBatch::FloatBatch(const FloatBatch& copy) : batches(copy.batches), remainders(copy.remainders) {}

    FloatBatch::FloatBatch(const FloatBatch* copy) : batches(copy->batches), remainders(copy->remainders) {}

    size_t FloatBatch::size() const {
        return batches.size() * float_batch::size + remainders.size();
    }

    FloatBatch FloatBatch::operator * (const FloatBatch& rhs) const {
        FloatBatch out = FloatBatch(std::vector<float> {});

        for (size_t i = 0; i < batches.size(); ++i) {
            out.batches.push_back(batches[i] * rhs.batches[i]);
        }

        for (size_t i = 0; i < remainders.size(); ++i) {
            out.remainders.push_back(remainders[i] * rhs.remainders[i]);
        }

        return out;
    }

}
