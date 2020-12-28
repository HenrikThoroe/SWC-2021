#include <stdexcept>

#include "DNN.hpp"

namespace ML {

    DNN::DNN(std::vector<Layer> layers) : layers(layers) {}

    DNN::DNN(std::vector<uint16_t> dimensions, std::vector<ActivationFunction::Type> layerTypes) {
        if (dimensions.size() != layerTypes.size() + 1) {
            throw std::runtime_error("Dimensions has to be equal to layerTypes + 1");
        }

        if (dimensions.size() < 2) {
            throw std::runtime_error("Dimensions has to contain at least two values (input & output layer)");
        }

        for (int i = 1; i < dimensions.size(); ++i) {
            layers.emplace_back(dimensions[i - 1], dimensions[i], layerTypes[i - 1]);
        }
    }

    std::vector<float> DNN::predict(const std::vector<float>& input) const {
        std::vector<float> res = input;

        for (const Layer& layer : layers) {
            res = layer.feed(res);
        }

        return res;
    }

}
