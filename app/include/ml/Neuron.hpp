#pragma once 

#include <vector>
#include <inttypes.h>

#include "ActivationFunction.hpp"

namespace ML {

    class Neuron {
        private:
            std::vector<float> weights;

        public:

            const ActivationFunction::Type activation;

            Neuron(std::vector<float> weights, ActivationFunction::Type activation);

            Neuron(uint16_t size, ActivationFunction::Type activation);

            float fire(const std::vector<float>& input) const;
    };

}
