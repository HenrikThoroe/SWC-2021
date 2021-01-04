#pragma once 

#include <vector>

#include "Layer.hpp"

namespace ML {

    class DNN {
        private:
            std::vector<Layer> layers;

            bool useBias;
            
        public:

            DNN(std::vector<int> dimensions, std::vector<ActivationFunction::Type> layerTypes, bool biased);

            const std::vector<float>& predict(std::vector<float> input);
    };

}
