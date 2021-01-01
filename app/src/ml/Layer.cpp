#include <thread>

#include "Layer.hpp"
#include "FloatBatch.hpp"

namespace ML {

    Layer::Layer(std::vector<Neuron> neurons) : neurons(neurons) {}

    Layer::Layer(uint16_t inputSize, uint16_t outputSize, ActivationFunction::Type activation) : neurons({}) {
        for (uint16_t i = 0; i < outputSize; ++i) {
            neurons.emplace_back(inputSize, activation);
        }
    }

    std::vector<float> Layer::feed(const std::vector<float>& input) const {
        std::vector<float> out{};
        FloatBatch in = FloatBatch(input);

        out.resize(neurons.size());

        for (size_t i = 0; i < neurons.size(); ++i) {
            out[i] = neurons[i].fire(in);
        }

        return out;
    }

    int Layer::size() const {
        return neurons.size();
    }

}
