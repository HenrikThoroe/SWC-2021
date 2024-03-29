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

    SECTION("Operators Are Working") {
        REQUIRE(pos + Util::Vector2D(2, 1) == Util::Position(4, 4));
        REQUIRE(pos - Util::Vector2D(2, 1) == Util::Position(0, 2));
        REQUIRE(pos - Util::Vector2D(2, 1) + Util::Vector2D(1, 1) == Util::Position(1, 3));
    }

    SECTION("Can Detect Neighbours") {
        auto edges = pos.getEdges();

        REQUIRE(edges[0] == Util::Position(1, 3));
        REQUIRE(edges[1] == Util::Position(3, 3));
        REQUIRE(edges[2] == Util::Position(2, 2));
        REQUIRE(edges[3] == Util::Position(2, 4));

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
