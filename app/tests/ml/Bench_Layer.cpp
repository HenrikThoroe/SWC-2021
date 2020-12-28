#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "Layer.hpp"

using namespace ML;

TEST_CASE("Bench Layer", "[benchmark][ml]") {
    Layer layer_4x1 = Layer(4, 1, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_16x2 = Layer(16, 1, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_512x1 = Layer(512, 1, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_512x16 = Layer(512, 16, ActivationFunction::Type::LEAKY_RELU);

    std::vector<float> input_16{};
    std::vector<float> input_512{};

    for (int i = 0; i < 16; ++i) {
        input_16.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    }

    for (int i = 0; i < 512; ++i) {
        input_512.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
    }

    BENCHMARK("[4, 1]") {
        return layer_4x1.feed({ 0.5, 0.3, 0.6, 0.8 });
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
}
