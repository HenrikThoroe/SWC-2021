#pragma once

#include <vector>
#include <inttypes.h>

#include "ActivationFunction.hpp"
#include "FloatBatch.hpp"

namespace ML {

    /// A layer for use in a neural network
    class Layer {
        protected:
            /// The neurons of the layer. Each represented by its weights loaded into SIMD registers
            std::vector<FloatBatch> neurons;

            /// The shared activation function of all neurons
            ActivationFunction::Type activation;

            /// The most recent output of the layer
            std::vector<float> output {};

            /// The dot products of the last input times the neurons
            std::vector<float> dotProducts {};

            /// The last input which produced the most recent output
            std::vector<float> lastInput {};

            /// The accepted size of the input vector
            int inputSize;

        public:

            /// Creates a new randomly initialized object with the given dimension and metadata
            Layer(int inputSize, int outputSize, ActivationFunction::Type activation);

            /**
             * @brief Feeds the layer with the given input
             * 
             * @returns A mutable refernce to the (stored) output
             */
            std::vector<float>& feed(const std::vector<float>& input);

            /// The number of neurons aka the output size
            int size() const;

            /// The number of weights of each neuron aka the input size
            int weightsPerNeuron() const;
    };

}
