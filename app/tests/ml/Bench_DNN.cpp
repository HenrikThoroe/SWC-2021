#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "DNN.hpp"

#include "randomVector.hpp"

using namespace ML;

TEST_CASE("Bench DNN", "[benchmark][ml]") {
    DNN net_4x2x1 = DNN({ 4, 2, 1 }, { ActivationFunction::Type::LEAKY_RELU, ActivationFunction::Type::SIGMOID });
    DNN net_400x200x1 = DNN({ 400, 200, 1 }, { ActivationFunction::Type::LEAKY_RELU, ActivationFunction::Type::SIGMOID });

    BENCHMARK("[4, 2, 1]") {
        return net_4x2x1.predict(Util::randomVector(4));
    };

    BENCHMARK("[400, 200, 1]") {
        return net_400x200x1.predict(Util::randomVector(400));
    };
}
