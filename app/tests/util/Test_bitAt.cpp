#include "catch.hpp"
#include "bitAt.hpp"

using namespace Util;

TEST_CASE("Test Bit At") {
    int i32 = 0b0100;
    uint8_t u8 = 0b00000100;

    REQUIRE(bitAt(i32, 29) == 1);
    REQUIRE(bitAt(i32, 28) == 0);
    REQUIRE(bitAt(i32, 30) == 0);
    REQUIRE(bitAt(i32, 31) == 0);

    REQUIRE(bitAt(u8, 0) == 0);
    REQUIRE(bitAt(u8, 1) == 0);
    REQUIRE(bitAt(u8, 2) == 0);
    REQUIRE(bitAt(u8, 3) == 0);
    REQUIRE(bitAt(u8, 4) == 0);
    REQUIRE(bitAt(u8, 5) == 1);
    REQUIRE(bitAt(u8, 6) == 0);
    REQUIRE(bitAt(u8, 7) == 0);
}