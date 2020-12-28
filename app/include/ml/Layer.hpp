#pragma once

#include <vector>
#include <inttypes.h>

#include "ActivationFunction.hpp"
#include "Neuron.hpp"

namespace ML {

    class Layer {
        private:
            std::vector<Neuron> neurons;

        public:
            Layer(std::vector<Neuron> neurons);

            Layer(uint16_t inputSize, uint16_t outputSize, ActivationFunction::Type activation);

            std::vector<float> feed(const std::vector<float>& input) const;

            int size() const;
    };

}
