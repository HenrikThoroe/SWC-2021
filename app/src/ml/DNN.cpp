#include <stdexcept>

#include "DNN.hpp"

namespace ML {

    DNN::DNN(std::vector<std::vector<std::vector<float>>> weights, std::vector<ActivationFunction::Type> layerTypes, bool biased)  : lastLayerOutput({}), useBias(biased), inputLayer(weights[0], layerTypes[0]) {
        if (weights.size() < 1) {
            throw std::runtime_error("At least one layer is required to create a neural network");
        }

        if (weights.size() != layerTypes.size()) {
            throw std::runtime_error("Each layer requires an activation function");
        }

        layers.push_back(&inputLayer);

        for (int i = 1; i < weights.size(); ++i) {
            hiddenLayers.emplace_back(weights[i], layerTypes[i]);
            layers.push_back(&hiddenLayers[i - 1]);
        }
    }

    DNN::DNN(std::vector<int> dimensions, std::vector<ActivationFunction::Type> layerTypes, bool biased) : lastLayerOutput({}), useBias(biased), inputLayer(dimensions[0] + static_cast<int>(biased), dimensions[1], layerTypes[0]) {
        if (dimensions.size() != layerTypes.size() + 1) {
            throw std::runtime_error("Dimensions has to be equal to layerTypes + 1");
        }

        if (dimensions.size() < 2) {
            throw std::runtime_error("Dimensions has to contain at least two values (input & output layer)");
        }

        int bias = useBias ? 1 : 0;
        layers.push_back(&inputLayer);

        for (int i = 2; i < dimensions.size(); ++i) {
            hiddenLayers.emplace_back(dimensions[i - 1] + bias, dimensions[i], layerTypes[i - 1]);
            layers.push_back(&hiddenLayers[i - 2]);
        }
    }

    const std::vector<float>& DNN::predict(std::vector<float> input) {
        insertBias(inputLayer, input);
        lastLayerOutput = inputLayer.feed(input);
        propagateHiddenLayers();
        return lastLayerOutput;
    }

    const std::vector<float>& DNN::update(std::vector<float> input) {
        insertBias(inputLayer, input);

        bool hadUpdate = false;

        for (int idx = 0; idx < input.size(); ++idx) {
            if (inputLayer.requiresUpdate(input[idx], idx)) {
                lastLayerOutput = inputLayer.update(input[idx], idx);
                hadUpdate = true;
            }
        }

        if (!hadUpdate) {
            return lastLayerOutput;
        }

        propagateHiddenLayers();

        return lastLayerOutput;
    }

    void DNN::insertBias(const Layer& layer, std::vector<float>& input) {
        if (useBias && input.size() == layer.weightsPerNeuron() - 1) {
            input.push_back(1);
        }
    }

    void DNN::propagateHiddenLayers() {
        for (Layer& layer : hiddenLayers) {
            insertBias(layer, lastLayerOutput);
            lastLayerOutput = layer.feed(lastLayerOutput);
        }
    }

    int DNN::size() const {
        return layers.size();
    }

}
