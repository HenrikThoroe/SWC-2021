#include <string>

#include "Layer.hpp"
#include "ActivationFunction.hpp"
#include "FloatBatch.hpp"
#include "randomVector.hpp"

namespace ML {

    Layer::Layer(std::vector<std::vector<float>> weights, ActivationFunction::Type activation) : output({}), lastInput({}), dotProducts({}), activation(activation), neurons({}) {
        neurons.reserve(weights.size());
        output.resize(weights.size());
        dotProducts.resize(weights.size());

        int weightsCount = -1;
        for (const std::vector<float>& neuronWeights : weights) {
            if (neuronWeights.size() != weightsCount && weightsCount != -1) {
                throw std::runtime_error("Not all neurons are of the same size");
            }

            weightsCount = neuronWeights.size();
            neurons.emplace_back(neuronWeights);
        }

        lastInput.resize(weightsCount);
        inputSize = weightsCount;
    }

    Layer::Layer(int inputSize, int outputSize, ActivationFunction::Type activation) : output({}), lastInput({}), dotProducts({}), inputSize(inputSize), activation(activation), neurons({}) {
        neurons.reserve(outputSize);
        output.resize(outputSize);
        lastInput.resize(inputSize);
        dotProducts.resize(outputSize);

        for (int i = 0; i < outputSize; ++i) {
            neurons.emplace_back(Util::randomVector(static_cast<uint32_t>(inputSize)));
        }
    }

    std::vector<float>& Layer::feed(const std::vector<float>& input) {
        FloatBatch in = FloatBatch(input);

        std::copy(input.begin(), input.end(), lastInput.begin());

        for (int i = 0; i < neurons.size(); ++i) {
            const FloatBatch& neuron = neurons[i];
            dotProducts[i] = 0;

            for (int x = 0; x < neuron.batches.size(); ++x) {
                dotProducts[i] += xsimd::hadd(neuron.batches[x] * in.batches[x]);
            }

            for (int x = 0; x < neuron.remainders.size(); ++x) {
                dotProducts[i] += neuron.remainders[x] * in.remainders[x];
            }

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

                case ActivationFunction::Type::TANH:
                    output[i] = ActivationFunction::tanh(dotProducts[i]);
                    break;

                case ActivationFunction::Type::STRETCHED_SIGMOID:
                    output[i] = ActivationFunction::stretchedSigmoid(dotProducts[i]);
                    break;

                default:
                    throw std::runtime_error("Unknown Activation Function " + std::to_string(static_cast<int>(activation)));
            }
        }

        return output;
    }

    int Layer::size() const {
        return neurons.size();
    }

    int Layer::weightsPerNeuron() const {
        return inputSize;
    }

}
