#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "DNN.hpp"

#include "randomVector.hpp"

using namespace ML;

TEST_CASE("Bench DNN", "[benchmark][ml][net]") {
    DNN net_4x2x1 = DNN({ 4, 2, 1 }, { ActivationFunction::Type::LEAKY_RELU, ActivationFunction::Type::SIGMOID }, true);
    DNN net_400x200x1 = DNN({ 400, 200, 1 }, { ActivationFunction::Type::LEAKY_RELU, ActivationFunction::Type::SIGMOID }, true);
    DNN net_88x44x1 = DNN({ 88, 44, 22, 1 }, { ActivationFunction::Type::LINEAR, ActivationFunction::Type::LEAKY_RELU, ActivationFunction::Type::SIGMOID }, true);

    std::vector<float> input_4 = Util::randomVector(4);
    std::vector<float> input_400 = Util::randomVector(400);
    std::vector<float> input_88 = Util::randomVector(88);

    BENCHMARK("[4, 2, 1]") {
        return net_4x2x1.predict(input_4);
    };

    BENCHMARK("[400, 200, 1]") {
        return net_400x200x1.predict(input_400);
    };

    BENCHMARK("[88, 44, 22, 1]") {
        return net_88x44x1.predict(input_88);
    };
}
