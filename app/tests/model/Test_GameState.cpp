#include "catch.hpp"
#include "GameState.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("Test Game State", "[model]") {
    GameState state = GameState();
    Move m1 = Move(20, PieceColor::BLUE, Rotation::ONEHALFPI, Vector2D(1, 1), Position(0, 0));

    SECTION("Validate Move") {
        Move m2 = Move(20, PieceColor::BLUE, Rotation::PI, Vector2D(1, 1), Position(0, 0));

        REQUIRE(state.canBeDeployed(m1));
        REQUIRE_FALSE(state.canBeDeployed(m2));
    }

    state.performMove(m1);

    SECTION("Can Perform Move") {
        REQUIRE(state.getTurn() == 1);
        REQUIRE(state.getCurrentPlayer().color == PlayerColor::RED);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::RED);
    }

    state.revertLastMove();

    SECTION("Can Revert Move") {
        REQUIRE(state.getTurn() == 0);
        REQUIRE(state.getCurrentPlayer().color == PlayerColor::BLUE);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::BLUE);
    }

    SECTION("Can Hash") {
        for (int x = 0; x < 30; ++x) {
            std::vector<const Move*> moves = state.getPossibleMoves();

            if (moves.size() == 0) {
                FAIL(state);
            }

            int index = rand() % moves.size();

            state.performMove(*moves[index]);

            WARN(state.hash());
        }

        for (int x = 0; x < 30; ++x) {
            state.revertLastMove();
            WARN(state.hash());
        }
    }
}