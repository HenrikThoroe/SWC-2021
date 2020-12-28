#include "Layer.hpp"

namespace ML {

    Layer::Layer(std::vector<Neuron> neurons) : neurons(neurons) {}

    Layer::Layer(uint16_t inputSize, uint16_t outputSize, ActivationFunction::Type activation) : neurons({}) {
        for (uint16_t i = 0; i < outputSize; ++i) {
            neurons.emplace_back(inputSize + 1, activation);
        }
    }

    std::vector<float> Layer::feed(const std::vector<float>& input) const {
        std::vector<float> out{};

        for (const Neuron& neuron : neurons) {
            out.push_back(neuron.fire(input));
        }

        return out;
    }

    int Layer::size() const {
        return neurons.size();
    }

}
