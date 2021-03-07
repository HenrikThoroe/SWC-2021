#include "catch.hpp"
#include "Rect.hpp"

using namespace Util;

TEST_CASE("Rect Test", "[util]") {
    Rect rect = Rect(2, 10, 3, 11);

    SECTION("Can calculate dimensions") {
        REQUIRE(rect.width() == 9);
        REQUIRE(rect.height() == 9);
        REQUIRE(rect.size() == 81);
        REQUIRE(rect.diagonal() > 12.7);
        REQUIRE(rect.diagonal() < 12.8);
    }

    SECTION("Can join with other rect") {
        Rect other = Rect(0, 4, 1, 7);
        Rect joined = rect.join(other);

        REQUIRE(joined.minX == 0);
        REQUIRE(joined.minY == 1);
        REQUIRE(joined.maxX == 10);
        REQUIRE(joined.maxY == 11);
        REQUIRE(joined.width() == 11);
        REQUIRE(joined.height() == 11);
        REQUIRE(joined.size() == 121);
    }
}
