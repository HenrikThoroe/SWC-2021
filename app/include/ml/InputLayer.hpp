#pragma once 

#include "Layer.hpp"

namespace ML {

    class InputLayer : public Layer {
        public:
            InputLayer(int inputSize, int outputSize, ActivationFunction::Type activation);
            
            const std::vector<float>& update(float input, int index);
    };

}
