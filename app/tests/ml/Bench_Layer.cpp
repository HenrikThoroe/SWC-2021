#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "Layer.hpp"

#include "randomVector.hpp"

using namespace ML;

TEST_CASE("Bench Layer", "[benchmark][ml][layer]") {
    Layer layer_4x1 = Layer(4, 1, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_16x2 = Layer(16, 1, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_512x1 = Layer(512, 1, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_512x16 = Layer(512, 16, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_4096x1 = Layer(4096, 1, ActivationFunction::Type::LEAKY_RELU);

    std::vector<float> input_4 = Util::randomVector(4);
    std::vector<float> input_16 = Util::randomVector(16);
    std::vector<float> input_512 = Util::randomVector(512);
    std::vector<float> input_4096 = Util::randomVector(4096);

    BENCHMARK("[4, 1]") {
        return layer_4x1.feed(input_4);
    };

    BENCHMARK("[16, 2]") {
        return layer_16x2.feed(input_16);
    };

    BENCHMARK("[512, 1]") {
        return layer_512x1.feed(input_512);
    };

    BENCHMARK("[512, 16]") {
        return layer_512x16.feed(input_512);
    };

    BENCHMARK("[4096, 1]") {
        return layer_4096x1.feed(input_4096);
    };

}
