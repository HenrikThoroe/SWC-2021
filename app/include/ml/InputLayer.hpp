#pragma once 

#include "Layer.hpp"

namespace ML {

    class InputLayer : public Layer {
        public:
            InputLayer(int inputSize, int outputSize, ActivationFunction::Type activation);
            
            std::vector<float>& update(float input, int index);

            bool requiresUpdate(float value, int index) const;
    };

}
