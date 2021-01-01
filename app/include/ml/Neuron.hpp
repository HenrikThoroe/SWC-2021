#pragma once 

#include <vector>
#include <inttypes.h>
#include "xsimd.hpp"

#include "ActivationFunction.hpp"
#include "FloatBatch.hpp"

namespace ML {

    class Neuron {
        private:

            FloatBatch weights;

        public:

            const ActivationFunction::Type activation;

            Neuron(const std::vector<float>& weights, ActivationFunction::Type activation);

            Neuron(uint16_t size, ActivationFunction::Type activation);

            float fire(const FloatBatch& input) const;
    };

}
