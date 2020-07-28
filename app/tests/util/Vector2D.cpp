#include "catch.hpp"
#include "Vector2D.hpp"

TEST_CASE("Mathematical Vector Test", "[util]") {
    auto vec = Util::Vector2D(5, -3);

    REQUIRE(vec.x == 5);
    REQUIRE(vec.y == -3);

    SECTION("Nonmutating Methods are Working") {
        double length = vec.length();
        auto scaled = vec.scaled(2);
        auto scaledNeg = vec.scaled(-2);
        auto shifted = vec.shifted(Util::Vector2D(2, 3));
        auto shiftedNeg = vec.shifted(Util::Vector2D(-2, -3));

        REQUIRE(length == sqrt(34));

        REQUIRE(scaled.x == 10);
        REQUIRE(scaled.y == -6);

        REQUIRE(scaledNeg.x == -10);
        REQUIRE(scaledNeg.y == 6);

        REQUIRE(shifted.x == 7);
        REQUIRE(shifted.y == 0);

        REQUIRE(shiftedNeg.x == 3);
        REQUIRE(shiftedNeg.y == -6);
    }

    SECTION("Mutating Methods are Working") {
        vec.scale(2);

        REQUIRE(vec.x == 10);
        REQUIRE(vec.y == -6);

        vec.scale(-2);

        REQUIRE(vec.x == -20);
        REQUIRE(vec.y == 12);

        vec.shift(Util::Vector2D(2, 3));

        REQUIRE(vec.x == -18);
        REQUIRE(vec.y == 15);

        vec.shift(Util::Vector2D(-2, -3));

        REQUIRE(vec.x == -20);
        REQUIRE(vec.y == 12);
    }

    SECTION("Operators are Working") {
        vec = Util::Vector2D(5, -3);
        auto sec = Util::Vector2D(3, 9);
        auto third = Util::Vector2D(10, -6);
        auto added = vec + sec;
        auto scaled = vec * 6;

        REQUIRE(added.x == 8);
        REQUIRE(added.y == 6);
        REQUIRE(scaled.x == 5 * 6);
        REQUIRE(scaled.y == -3 * 6);
        REQUIRE_FALSE(vec == sec);
        REQUIRE(vec * 2 == third);
    }
}