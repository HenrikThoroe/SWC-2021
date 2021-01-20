#include <stdexcept>
#include "json.hpp"

#include "DNN.hpp"

using JSON = nlohmann::json;

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
        firstRun = false;
        insertBias(inputLayer, input);
        lastLayerOutput = inputLayer.feed(input);
        propagateHiddenLayers();
        return lastLayerOutput;
    }

    const std::vector<float>& DNN::update(std::vector<float> input) {
        if (firstRun) {
            return predict(input);
        }

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

    std::unique_ptr<DNN> DNN::fromJSON(const std::string& raw) {
        JSON json = JSON::parse(raw.c_str());

        // Verify version to avoid parsing errors
        if (json["version"].get<std::string>() != "1.0.0") {
            throw std::runtime_error("Unknown model version: " + json["version"].get<std::string>());
        }

        bool useBias = json["bias"].get<bool>();
        int inputSize = json["inputSize"].get<int>();
        std::vector<std::vector<std::vector<float>>> weights{};
        std::vector<ActivationFunction::Type> activations{};
        std::vector<int> dimensions { inputSize };

        // Fetch metadata of the network: number of neurons per layer + layer activation functions
        for (const JSON& layer : json["schema"].items()) {
            for (const JSON& info : layer) {
                dimensions.push_back(info["neurons"].get<int>());
                std::string activation = info["activation"].get<std::string>();

                if (activation == "leakyReLU") {
                    activations.push_back(ActivationFunction::Type::LEAKY_RELU);
                } else if (activation == "linear") {
                    activations.push_back(ActivationFunction::Type::LINEAR);
                } else if (activation == "sigmoid") {
                    activations.push_back(ActivationFunction::Type::SIGMOID);
                } else if (activation == "binary") {
                    activations.push_back(ActivationFunction::Type::BINARY);
                } else if (activation == "tanh") {
                    activations.push_back(ActivationFunction::Type::TANH);
                } else {
                    throw std::runtime_error("Unknown activation function: " + activation);
                }
            }
        }

        // Read weights of all neurons in the network
        for (auto it = json["weights"].begin(); it < json["weights"].end(); ++it) {
            weights.push_back({});
            for (auto it2 = it.value().begin(); it2 < it.value().end(); ++it2) {
                weights.back().push_back({});
                for (const JSON& weight : it2.value()) {
                    weights.back().back().push_back(weight.get<float>());
                }
            }
        }

        // If bias should be used read bias values and append to each neuron weights
        if (useBias) {
            int layer = 0;
            for (auto it = json["biases"].begin(); it < json["biases"].end(); ++it) {
                int neuron = 0;
                for (const JSON& bias : it.value()) {
                    weights[layer][neuron].push_back(bias.get<float>());
                    neuron += 1;
                }

                layer += 1;
            }
        }

        // Verify data

        // Verify number of layers
        if (dimensions.size() - 1 != weights.size()) {
            throw std::runtime_error("Number of weights does not conform with number of layers");
        }

        // Verify that at least one layer is available
        if (dimensions.size() < 2) {
            throw std::runtime_error("JSON has to describe at least one layer");
        }

        for (int i = 1; i < dimensions.size(); ++i) {
            // Verify that network metadata and number of weights conform
            if (weights[i - 1].size() != dimensions[i]) {
                throw std::runtime_error("Too many weights are described in JSON file");
            }

            // Verify that every neuron has as many weights (+ bias) as the previous layer has outputs
            for (const std::vector<float>& neuron : weights[i - 1]) {
                if (neuron.size() != dimensions[i - 1] + useBias ? 1 : 0) {
                    throw std::runtime_error("Not all neurons have sufficient weights to form a fully conected network");
                }
            }
        }

        return std::make_unique<DNN>(weights, activations, useBias);
    }

}
