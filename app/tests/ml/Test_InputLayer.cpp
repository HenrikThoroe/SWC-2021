#include "catch.hpp"
#include "InputLayer.hpp"

#include "randomVector.hpp"
#include "compareFloat.hpp"

using namespace ML;

TEST_CASE("Test Input Layer", "[ml]") {
    InputLayer layer_4x1 = InputLayer(4, 1, ActivationFunction::Type::LEAKY_RELU);
    InputLayer layer_16x2 = InputLayer(16, 2, ActivationFunction::Type::LEAKY_RELU);
    InputLayer layer_512x1 = InputLayer(512, 1, ActivationFunction::Type::LEAKY_RELU);
    InputLayer layer_512x16 = InputLayer(512, 16, ActivationFunction::Type::LEAKY_RELU);
    InputLayer layer_4096x1 = InputLayer(4096, 1, ActivationFunction::Type::LEAKY_RELU);

    std::vector<float> input_4 = Util::randomVector(4);
    std::vector<float> input_16 = Util::randomVector(16);
    std::vector<float> input_512 = Util::randomVector(512);
    std::vector<float> input_4096 = Util::randomVector(4096);

    std::vector<InputLayer*> layers = {
        &layer_4x1,
        &layer_16x2,
        &layer_512x1,
        &layer_512x16,
        &layer_4096x1
    };

    std::vector<std::vector<float>*> inputs = {
        &input_4,
        &input_16,
        &input_512,
        &input_512,
        &input_4096
    };

    SECTION("Output Does Not Change for Equal Input") {
        for (int l = 0; l < layers.size(); ++l) {
            auto out1 = layers[l]->feed(*inputs[l]);
            auto out2 = layers[l]->update((*inputs[l])[0], 0);

            REQUIRE(out1.size() == out2.size());

            for (int i = 0; i < out1.size(); ++i) {
                REQUIRE(Util::compareFloat(out1[i], out2[i]));
            }
        }
    }

    SECTION("Output Changes for Different Input") {
        for (int l = 0; l < layers.size(); ++l) {
            auto out1 = layers[l]->feed(*inputs[l]);
            auto out2 = layers[l]->update(0.9, 0);

            REQUIRE(out1.size() == out2.size());

            for (int i = 0; i < out1.size(); ++i) {
                REQUIRE(!Util::compareFloat(out1[i], out2[i]));
            }
        }
    }
}
