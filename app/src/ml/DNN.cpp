#include <stdexcept>

#include "DNN.hpp"

namespace ML {

    DNN::DNN(std::vector<int> dimensions, std::vector<ActivationFunction::Type> layerTypes, bool biased) : useBias(biased) {
        if (dimensions.size() != layerTypes.size() + 1) {
            throw std::runtime_error("Dimensions has to be equal to layerTypes + 1");
        }

        if (dimensions.size() < 2) {
            throw std::runtime_error("Dimensions has to contain at least two values (input & output layer)");
        }

        int bias = useBias ? 1 : 0;

        for (int i = 1; i < dimensions.size(); ++i) {
            layers.emplace_back(dimensions[i - 1] + bias, dimensions[i], layerTypes[i - 1]);
        }
    }

    const std::vector<float>& DNN::predict(std::vector<float> input) {
        std::vector<float>& lastOutput = input;

        for (Layer& layer : layers) {
            if (useBias && lastOutput.size() == layer.weightsPerNeuron() - 1) {
                lastOutput.push_back(1);
            }

            lastOutput = layer.feed(lastOutput);
        }

        return lastOutput;
    }

}
