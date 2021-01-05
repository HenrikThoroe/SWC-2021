#pragma once 

#include <vector>

#include "Layer.hpp"
#include "InputLayer.hpp"

namespace ML {

    class DNN {
        private:

            std::vector<Layer*> layers;

            bool useBias;

            InputLayer inputLayer;

            std::vector<Layer> hiddenLayers;

            std::vector<float> lastLayerOutput;
            
        public:

            DNN(std::vector<int> dimensions, std::vector<ActivationFunction::Type> layerTypes, bool biased);

            const std::vector<float>& predict(std::vector<float> input);

            int size() const;

            const std::vector<float>& update(std::vector<float> input);

        private:

            void propagateHiddenLayers();

            void insertBias(const Layer& layer, std::vector<float>& input);
    };

}
