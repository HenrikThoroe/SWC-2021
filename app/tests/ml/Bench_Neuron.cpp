#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "Neuron.hpp"

using namespace ML;

TEST_CASE("Bench Neuron", "[benchmark][ml]") {
    std::vector<float> weights_x4{};
    std::vector<float> weights_x16{};
    std::vector<float> weights_x64{};
    std::vector<float> weights_x256{};
    std::vector<float> weights_x512{};
    std::vector<float> weights_x1024{};

    std::vector<float> input_x4{};
    std::vector<float> input_x16{};
    std::vector<float> input_x64{};
    std::vector<float> input_x256{};
    std::vector<float> input_x512{};
    std::vector<float> input_x1024{};

    for (int i = 0; i < 4; ++i) {
        weights_x4.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

        if (i > 0) {
            input_x4.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
    }

    for (int i = 0; i < 16; ++i) {
        weights_x16.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

        if (i > 0) {
            input_x16.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
    }

    for (int i = 0; i < 64; ++i) {
        weights_x64.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

        if (i > 0) {
            input_x64.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
    }

    for (int i = 0; i < 256; ++i) {
        weights_x256.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

        if (i > 0) {
            input_x256.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
    }

    for (int i = 0; i < 512; ++i) {
        weights_x512.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

        if (i > 0) {
            input_x512.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
    }

    for (int i = 0; i < 1024; ++i) {
        weights_x1024.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

        if (i > 0) {
            input_x1024.push_back(static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
        }
    }

    Neuron neuron_x4 = Neuron(weights_x4, ActivationFunction::Type::LEAKY_RELU);
    Neuron neuron_x16 = Neuron(weights_x16, ActivationFunction::Type::LEAKY_RELU);
    Neuron neuron_x64 = Neuron(weights_x64, ActivationFunction::Type::LEAKY_RELU);
    Neuron neuron_x256 = Neuron(weights_x256, ActivationFunction::Type::LEAKY_RELU);
    Neuron neuron_x512 = Neuron(weights_x512, ActivationFunction::Type::LEAKY_RELU);
    Neuron neuron_x1024 = Neuron(weights_x1024, ActivationFunction::Type::LEAKY_RELU);

    BENCHMARK("x4") {
        return neuron_x4.fire(input_x4);
    };

    BENCHMARK("x16") {
        return neuron_x16.fire(input_x16);
    };

    BENCHMARK("x64") {
        return neuron_x64.fire(input_x64);
    };

    BENCHMARK("x256") {
        return neuron_x256.fire(input_x256);
    };

    BENCHMARK("x512") {
        return neuron_x512.fire(input_x512);
    };

    BENCHMARK("x1024") {
        return neuron_x1024.fire(input_x1024);
    };
}
