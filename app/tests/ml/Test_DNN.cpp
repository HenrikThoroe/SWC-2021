#include "catch.hpp"
#include "DNN.hpp"

#include "randomVector.hpp"
#include "compareFloat.hpp"
#include "loadAsset.hpp"

using namespace ML;

TEST_CASE("Test DNN", "[ml]") {
    DNN net_4x2x1 = DNN({ 4, 2, 1 }, { ActivationFunction::Type::LEAKY_RELU, ActivationFunction::Type::SIGMOID }, true);
    DNN net_400x200x10 = DNN({ 400, 200, 10 }, { ActivationFunction::Type::LEAKY_RELU, ActivationFunction::Type::SIGMOID }, true);
    DNN net_88x44x1 = DNN({ 88, 44, 22, 1 }, { ActivationFunction::Type::LEAKY_RELU, ActivationFunction::Type::LEAKY_RELU, ActivationFunction::Type::SIGMOID }, true);

    std::vector<float> input_4 = Util::randomVector(4);
    std::vector<float> input_400 = Util::randomVector(400);
    std::vector<float> input_88 = Util::randomVector(88);

    std::vector<DNN*> nets = {
        &net_4x2x1,
        &net_400x200x10,
        &net_88x44x1
    };

    std::vector<std::vector<float>*> inputs = {
        &input_4,
        &input_400,
        &input_88
    };

    SECTION("Has Correct Output Dimension") {
        REQUIRE(net_4x2x1.predict(input_4).size() == 1);
        REQUIRE(net_400x200x10.predict(input_400).size() == 10);
        REQUIRE(net_88x44x1.predict(input_88).size() == 1);
    }

    SECTION("Output Does Not Change for Equal Input") {
        for (int n = 0; n < nets.size(); ++n) {
            auto out1 = nets[n]->predict(*inputs[n]);
            auto out2 = nets[n]->predict(*inputs[n]);

            REQUIRE(out1.size() == out2.size());

            for (int i = 0; i < out1.size(); ++i) {
                REQUIRE(Util::compareFloat(out1[i], out2[i]));
            }
        }
    }

    SECTION("Output Changes for Different Input") {
        for (int n = 0; n < nets.size(); ++n) {
            auto out1 = nets[n]->predict(*inputs[n]);
            auto out2 = nets[n]->predict(Util::randomVector(inputs[n]->size()));

            REQUIRE(out1.size() == out2.size());

            for (int i = 0; i < out1.size(); ++i) {
                REQUIRE((!Util::compareFloat(out1[i], out2[i]) || (out1[i] == 1 && out2[i] == 1) || (out1[i] == 0 && out2[i] == 0)));
            }
        }
    }

    SECTION("Output Does Not Change for Equal Update-Input") {
        for (int n = 0; n < nets.size(); ++n) {
            auto out1 = nets[n]->predict(*inputs[n]);
            auto out2 = nets[n]->update(*inputs[n]);

            REQUIRE(out1.size() == out2.size());

            for (int i = 0; i < out1.size(); ++i) {
                REQUIRE(Util::compareFloat(out1[i], out2[i]));
            }
        }
    }

    SECTION("Output Changes for Different Update-Input") {
        for (int n = 0; n < nets.size(); ++n) {
            auto out1 = nets[n]->predict(*inputs[n]);
            auto out2 = nets[n]->update(Util::randomVector(inputs[n]->size()));

            REQUIRE(out1.size() == out2.size());

            for (int i = 0; i < out1.size(); ++i) {
                REQUIRE((!Util::compareFloat(out1[i], out2[i]) || (out1[i] == 1 && out2[i] == 1) || (out1[i] == 0 && out2[i] == 0)));
            }
        }
    }

    SECTION("Can be Constructed From Weights") {
        DNN net = DNN({ { { 0.5, 0.4 }, { 0.2, 0.3 } }, { { 0.7, 0.8 } } }, { ActivationFunction::Type::LINEAR, ActivationFunction::Type::LINEAR }, false);
        std::vector<float> res = net.predict({ 2, 1 });
        constexpr float expected = (0.5 * 2 + 0.4 * 1) * 0.7 + (0.2 * 2 + 0.3 * 1) * 0.8;

        REQUIRE(res.size() == 1);
        INFO(res[0]);
        INFO(expected);
        REQUIRE(Util::compareFloat(res[0], expected));
    }

    SECTION("Can be Constructed From Weights (+ Bias)") {
        DNN net = DNN({ { { 0.5, 0.4, 0.3 }, { 0.2, 0.3, 0.6 } }, { { 0.7, 0.8, 0.9 } } }, { ActivationFunction::Type::LINEAR, ActivationFunction::Type::LINEAR }, true);
        std::vector<float> res = net.predict({ 2, 1 });
        constexpr float expected = (0.5 * 2 + 0.4 * 1 + 0.3 * 1) * 0.7 + (0.2 * 2 + 0.3 * 1 + 0.6 * 1) * 0.8 + 0.9 * 1;

        REQUIRE(res.size() == 1);
        INFO(res[0]);
        INFO(expected);
        REQUIRE(Util::compareFloat(res[0], expected));
    }

    SECTION("Can be Created from JSON") {
        std::string json {};
        #pragma region networkJSON
        json = 
            "{"
            "   \"version\": \"1.0.0\","
            "   \"bias\": true,"
            "   \"inputSize\": 2,"
            "   \"schema\": ["
            "       {"
            "           \"neurons\": 2,"
            "           \"activation\": \"leakyReLU\""
            "       },"
            "       {"
            "           \"neurons\": 1,"
            "           \"activation\": \"sigmoid\""
            "       }"
            "   ],"
            "   \"biases\": ["
            "       ["
            "           4.1,"
            "           4.2"
            "       ],"
            "       ["
            "           4.3"
            "       ]"
            "   ],"
            "   \"weights\": ["
            "       ["
            "           ["
            "               1.1,"
            "               1.2"
            "           ],"
            "           ["
            "               2.1,"
            "               2.2"
            "           ]"
            "       ],"
            "       ["
            "           ["
            "               3.1,"
            "               3.2"
            "           ]"
            "       ]"
            "   ]"
            "}";
        #pragma endregion

        std::unique_ptr<DNN> net = DNN::fromJSON(json);

        REQUIRE(net->size() == 2);
        REQUIRE_NOTHROW(net->predict({ 1, 1 }));
        REQUIRE(net->predict({ 1, 1 }).size() == 1);
    }

    SECTION("Can Load XOR") {
        std::unique_ptr<DNN> xorNet = DNN::fromJSON(Util::loadAsset(Util::Asset::XOR_NETWORK));

        REQUIRE(xorNet->size() == 2);
        REQUIRE(xorNet->predict({ 0, 1 }).size() == 1);
        REQUIRE(xorNet->predict({ 0, 1 })[0] > 0.9);
        REQUIRE(xorNet->predict({ 1, 1 })[0] < 0.1);
        REQUIRE(xorNet->predict({ 0, 0 })[0] < 0.1);
        REQUIRE(xorNet->predict({ 1, 0 })[0] > 0.9);
    }
}