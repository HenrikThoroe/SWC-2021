#pragma once 

#include <vector>

#include "ActivationFunction.hpp"

namespace ML {

    class Neuron {
        public:
            const std::vector<float> weights;

            const ActivationFunction::Type activation;

            Neuron(std::vector<float> weights, ActivationFunction::Type activation);

            float fire(const std::vector<float>& input) const;
    };

}
