#include <stdexcept>
#include <string>

#include "Neuron.hpp"

namespace ML {

    Neuron::Neuron(std::vector<float> weights, ActivationFunction::Type activation) : weights(weights), activation(activation) {}

    Neuron::Neuron(uint16_t size, ActivationFunction::Type activation) : weights({}), activation(activation) {
        for (int i = 0; i < size; ++i) {
            weights.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
    }

    float Neuron::fire(const std::vector<float>& input) const {
        if (input.size() != weights.size() - 1) {
            throw std::runtime_error("Input size does not match weights [" + std::to_string(weights.size()) + ":" + std::to_string(input.size()) + "]");
        }

        float value = weights[0];

        for (int index = 0; index < input.size(); ++index) {
            value += input[index] * weights[index + 1];
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
