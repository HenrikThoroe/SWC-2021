#pragma once

#include <vector>
#include <inttypes.h>

#include "ActivationFunction.hpp"
#include "FloatBatch.hpp"

namespace ML {

    class Layer {
        protected:
            std::vector<FloatBatch> neurons;

            ActivationFunction::Type activation;

            std::vector<float> output {};

            std::vector<float> dotProducts {};

            std::vector<float> lastInput {};

            int inputSize;

        public:

            Layer(int inputSize, int outputSize, ActivationFunction::Type activation);

            const std::vector<float>& feed(const std::vector<float>& input);

            const std::vector<float>& update(float input, int index);

            int size() const;
    };

}
