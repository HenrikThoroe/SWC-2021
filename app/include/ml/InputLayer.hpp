#pragma once 

#include "Layer.hpp"

namespace ML {

    /// A variation of a `Layer` which can be efficently updated
    class InputLayer : public Layer {
        public:
            /// Creates a new randomly initialized object with the given dimension and metadata 
            InputLayer(int inputSize, int outputSize, ActivationFunction::Type activation);
            
            /// Updates the given index of the last input with the given value. **Important: Do not use before calling feed() at least once**
            std::vector<float>& update(float input, int index);

            /// Checks if the last input at the given index is not equal the the new value
            bool requiresUpdate(float value, int index) const;
    };

}
