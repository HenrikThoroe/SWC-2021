#pragma once 

#include <vector>

#include "Layer.hpp"
#include "InputLayer.hpp"

namespace ML {

    /// An updatable deep neural network
    class DNN {
        private:

            /// Pointers to all layers of the network
            std::vector<Layer*> layers;

            /// Indicates if a bias value should be added to the layer input
            bool useBias;

            /// The input layer
            InputLayer inputLayer;

            /// All remaining hidden layers (+ output layer if you want to differentiate)
            std::vector<Layer> hiddenLayers;

            /// The output of the last executed layer
            std::vector<float> lastLayerOutput;
            
        public:

            /// Creates a DNN with random weights and given dimensions and metadata
            DNN(std::vector<int> dimensions, std::vector<ActivationFunction::Type> layerTypes, bool biased);

            /**
             * @brief Predicts a result for the given input vector
             * 
             * @returns A constant reference to the output of the last layer. 
             *          It will change if the network is feeded with a different output. 
             *          Copy if the value must be stored.
             */
            const std::vector<float>& predict(std::vector<float> input);

            /// The number of used layers
            int size() const;

            /// Updates the network partially with the new input. If equal to the last one nothing will be computed. 
            const std::vector<float>& update(std::vector<float> input);

        private:

            /// Propagates the last output through the hidden layers
            void propagateHiddenLayers();

            /// Inserts a bias value to the input if `useBias` is true
            void insertBias(const Layer& layer, std::vector<float>& input);
    };

}
