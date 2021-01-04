#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "InputLayer.hpp"

#include "randomVector.hpp"

using namespace ML;

TEST_CASE("Bench Input Layer", "[benchmark][ml][layer]") {
    InputLayer layer_4x1 = InputLayer(4, 1, ActivationFunction::Type::LEAKY_RELU);
    InputLayer layer_16x2 = InputLayer(16, 1, ActivationFunction::Type::LEAKY_RELU);
    InputLayer layer_512x1 = InputLayer(512, 1, ActivationFunction::Type::LEAKY_RELU);
    InputLayer layer_512x16 = InputLayer(512, 16, ActivationFunction::Type::LEAKY_RELU);
    InputLayer layer_4096x1 = InputLayer(4096, 1, ActivationFunction::Type::LEAKY_RELU);

    std::vector<float> input_4 = Util::randomVector(4);
    std::vector<float> input_16 = Util::randomVector(16);
    std::vector<float> input_512 = Util::randomVector(512);
    std::vector<float> input_4096 = Util::randomVector(4096);

    BENCHMARK("[4, 1] Update") {
        return layer_4x1.update(0.5, 3);
    };

    BENCHMARK("[16, 2] Update") {
        return layer_16x2.update(0.5, 3);
    };

    BENCHMARK("[512, 1] Update") {
        return layer_512x1.update(0.5, 3);
    };

    BENCHMARK("[512, 16] Update") {
        return layer_512x16.update(0.5, 3);
    };

    BENCHMARK("[4096, 1] Update") {
        return layer_4096x1.update(0.5, 3);
    };
}