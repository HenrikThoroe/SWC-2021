#include "catch.hpp"
#include "Layer.hpp"

#include "randomVector.hpp"
#include "compareFloat.hpp"

using namespace ML;

TEST_CASE("Test Layer", "[ml]") {
    Layer layer_4x1 = Layer(4, 1, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_16x2 = Layer(16, 2, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_512x1 = Layer(512, 1, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_512x16 = Layer(512, 16, ActivationFunction::Type::LEAKY_RELU);
    Layer layer_4096x1 = Layer(4096, 1, ActivationFunction::Type::LEAKY_RELU);

    std::vector<float> input_4 = Util::randomVector(4);
    std::vector<float> input_16 = Util::randomVector(16);
    std::vector<float> input_512 = Util::randomVector(512);
    std::vector<float> input_4096 = Util::randomVector(4096);

    std::vector<Layer*> layers = {
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

    SECTION("Has Correct Output Dimension") {
        REQUIRE(layer_4x1.feed(input_4).size() == 1);
        REQUIRE(layer_16x2.feed(input_16).size() == 2);
        REQUIRE(layer_512x1.feed(input_512).size() == 1);
        REQUIRE(layer_512x16.feed(input_512).size() == 16);
        REQUIRE(layer_4096x1.feed(input_4096).size() == 1);
    }

    SECTION("Output Does Not Change for Equal Input") {
        for (int l = 0; l < layers.size(); ++l) {
            auto out1 = layers[l]->feed(*inputs[l]);
            auto out2 = layers[l]->feed(*inputs[l]);

            REQUIRE(out1.size() == out2.size());

            for (int i = 0; i < out1.size(); ++i) {
                REQUIRE(Util::compareFloat(out1[i], out2[i]));
            }
        }
    }

    SECTION("Output Changes for Different Input") {
        for (int l = 0; l < layers.size(); ++l) {
            auto out1 = layers[l]->feed(*inputs[l]);
            auto out2 = layers[l]->feed(Util::randomVector(inputs[l]->size()));

            REQUIRE(out1.size() == out2.size());

            for (int i = 0; i < out1.size(); ++i) {
                REQUIRE(!Util::compareFloat(out1[i], out2[i]));
            }
        }
    }
}
