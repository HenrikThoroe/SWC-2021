#pragma once 

#include <vector>
#include <inttypes.h>

#include "Layer.hpp"

namespace ML {

    class DNN {
        private:
            std::vector<Layer> layers;
            
        public:

            DNN(std::vector<Layer> layers);

            DNN(std::vector<uint16_t> dimensions, std::vector<ActivationFunction::Type> layerTypes);

            std::vector<float> predict(const std::vector<float>& input) const;
    };

}
