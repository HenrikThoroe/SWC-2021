#include "InputLayer.hpp"

namespace ML {

    InputLayer::InputLayer(std::vector<std::vector<float>> weights, ActivationFunction::Type activation) : Layer(weights, activation) {}

    InputLayer::InputLayer(int inputSize, int outputSize, ActivationFunction::Type activation) : Layer(inputSize, outputSize, activation) {}

    std::vector<float>& InputLayer::update(float input, int index) {
        int avxRange = inputSize - (inputSize % float_batch::size);
        bool isRemaining = index >= avxRange;
        int idx = isRemaining ? index - avxRange : index / float_batch::size;
        int batchIdx = isRemaining ? -1 : index % float_batch::size;

        for (int i = 0; i < neurons.size(); ++i) {
            const FloatBatch& weight = neurons[i];

            float updatedWeight = isRemaining ? weight.remainders[idx] : weight.batches[idx][batchIdx];
            dotProducts[i] -= updatedWeight * lastInput[index];
            dotProducts[i] += updatedWeight * input;

            switch (activation) {
                case ActivationFunction::Type::LINEAR:
                    output[i] = ActivationFunction::linear(dotProducts[i]);
                    break;

                case ActivationFunction::Type::LEAKY_RELU:
                    output[i] = ActivationFunction::leakyReLU(dotProducts[i]);
                    break;

                case ActivationFunction::Type::SIGMOID:
                    output[i] = ActivationFunction::sigmoid(dotProducts[i]);
                    break;

                case ActivationFunction::Type::BINARY:
                    output[i] = ActivationFunction::binary(dotProducts[i]);
                    break;

                default:
                    throw std::runtime_error("Unknown Activation Function " + std::to_string(static_cast<int>(activation)));
            }
        }

        lastInput[index] = input;

        return output;
    }

    bool InputLayer::requiresUpdate(float value, int index) const {
        return lastInput[index] != value;
    }

}
