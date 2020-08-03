#include "catch.hpp"
#include "Player.hpp"

using namespace Model;

TEST_CASE("Player Test", "[model]") {
    auto red = Player(PlayerColor::RED);
    auto blue = Player(PlayerColor::BLUE);

    REQUIRE(red.color == PlayerColor::RED);
    REQUIRE(blue.color == PlayerColor::BLUE);

    SECTION("Player has Correct Piece Colors") {
        auto redColors = red.getPieceColors();
        auto blueColors = blue.getPieceColors();

        REQUIRE(redColors.size() == 2);
        REQUIRE(blueColors.size() == 2);

        REQUIRE(redColors[0] == PieceColor::RED);
        REQUIRE(redColors[1] == PieceColor::GREEN);
        REQUIRE(blueColors[0] == PieceColor::BLUE);
        REQUIRE(blueColors[1] == PieceColor::YELLOW);
    }

    SECTION("Can Invert It's Color") {
        red.invertColor();
        blue.invertColor();

        REQUIRE(red.color == PlayerColor::BLUE);
        REQUIRE(blue.color == PlayerColor::RED);
        REQUIRE(blue.getPieceColors()[0] == PieceColor::RED);
        REQUIRE(blue.getPieceColors()[1] == PieceColor::GREEN);
        REQUIRE(red.getPieceColors()[0] == PieceColor::BLUE);
        REQUIRE(red.getPieceColors()[1] == PieceColor::YELLOW);
    }
}