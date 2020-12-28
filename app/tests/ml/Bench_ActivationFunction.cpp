#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "ActivationFunction.hpp"

using namespace ML::ActivationFunction;

TEST_CASE("Bench Activation Functions", "[benchmark][ml]") {
    const float val = 0.9836718f;
    
    BENCHMARK("Sigmoid") {
        return sigmoid(val);
    };

    BENCHMARK("Leaky ReLU") {
        return leakyReLU(val);
    };

    BENCHMARK("Linear") {
        return linear(val);
    };

    BENCHMARK("Binary") {
        return binary(val);
    };

}
