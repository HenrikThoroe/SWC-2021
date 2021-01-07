#pragma once 

namespace ML::ActivationFunction {

    /// An enumeration to express which activation function should be used
    enum class Type {
        /// The classic sigmoid function. Within [0, 1]
        SIGMOID,

        /// Leaky rectified unit. Within [-Inf, Inf]
        LEAKY_RELU,

        /// Identity function
        LINEAR, 

        /// Binary step function. [0 + 1]
        BINARY,

        /// Tangens Hyperbolicus function. [-1, 1]
        TANH
    };

    /// Returns the computational expensive sigmoid value of x
    float sigmoid(float x);

    /// Returns the tangens hyperbolicus value of x
    float tanh(float x);

    /// Returns the leaky ReLU value of x
    float leakyReLU(float x);

    /// Returns the identity of x
    float linear(float x);

    /// Return 0 if x <= 0 otherwise 1
    float binary(float x);

}
