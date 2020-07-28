#include "catch.hpp"
#include "Position.hpp"

TEST_CASE("Position Test", "[util]") {
    auto pos = Util::Position(2, 3);
    auto dir = Util::Vector2D(4, -7);
    auto moved = pos.move(dir);
    auto added = pos + dir;

    REQUIRE(moved.x == 6);
    REQUIRE(moved.y == -4);
    REQUIRE(added.x == 6);
    REQUIRE(added.y == -4);

    SECTION("Can Detect Neighbours") {
        REQUIRE_FALSE(pos.isNextTo(pos));

        REQUIRE(pos.isNextTo(pos + Util::Vector2D(-1, -1)));
        REQUIRE(pos.isNextTo(pos + Util::Vector2D(0, -1)));
        REQUIRE(pos.isNextTo(pos + Util::Vector2D(1, -1)));

        REQUIRE(pos.isNextTo(pos + Util::Vector2D(-1, 1)));
        REQUIRE(pos.isNextTo(pos + Util::Vector2D(0, 1)));
        REQUIRE(pos.isNextTo(pos + Util::Vector2D(1, 1)));

        REQUIRE(pos.isNextTo(pos + Util::Vector2D(-1, 0)));
        REQUIRE(pos.isNextTo(pos + Util::Vector2D(1, 0)));
    }
}