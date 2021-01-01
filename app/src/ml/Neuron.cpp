#include <stdexcept>
#include <string>
#include <iostream>
#include "xsimd.hpp"

#include "Neuron.hpp"
#include "randomVector.hpp"

namespace ML {

    Neuron::Neuron(const std::vector<float>& weights, ActivationFunction::Type activation) : weights(weights), activation(activation) {}

    Neuron::Neuron(uint16_t size, ActivationFunction::Type activation) : Neuron(Util::randomVector(size), activation) {}

    float Neuron::fire(const FloatBatch& input) const {
        #ifdef DEBUG
        if (input.size() != weights.size()) {
            throw std::runtime_error("Input size does not match weights [" + std::to_string(weights.size()) + ":" + std::to_string(input.size()) + "]");
        }
        #endif

        float value = 0;

        for (size_t i = 0; i < weights.batches.size(); ++i) {
            value += xsimd::hadd(weights.batches[i] * input.batches[i]);
        }

        for (size_t i = 0; i < weights.remainders.size(); ++i) {
            value += weights.remainders[i] * input.remainders[i];
        }

        switch (activation) {
            case ActivationFunction::Type::LINEAR:
                return ActivationFunction::linear(value);
            case ActivationFunction::Type::LEAKY_RELU:
                return ActivationFunction::leakyReLU(value);
            case ActivationFunction::Type::SIGMOID:
                return ActivationFunction::sigmoid(value);
            case ActivationFunction::Type::BINARY:
                return ActivationFunction::binary(value);

            default:
                throw std::runtime_error("Unknown Activation Function");
        }
    }

}
