#pragma once 

namespace ML::ActivationFunction {

    enum class Type {
        SIGMOID,
        LEAKY_RELU,
        LINEAR, 
        BINARY
    };

    float sigmoid(float x);

    float leakyReLU(float x);

    float linear(float x);

    float binary(float x);

}
