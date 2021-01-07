#include <math.h>

#include "ActivationFunction.hpp"

namespace ML::ActivationFunction {

    float sigmoid(float x) {
        return 1 / (1 + expf(-x));
    }

    float leakyReLU(float x) {
        if (x > 0) {
            return x;
        } else {
            return 0.01 * x;
        }
    }

    float linear(float x) {
        return x;
    }

    float binary(float x) {
        if (x > 0) {
            return 1;
        } else {
            return 0;
        }
    }

    float tanh(float x) {
        return tanhf(x);
    }

}
