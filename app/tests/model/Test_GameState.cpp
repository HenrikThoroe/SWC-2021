#include "catch.hpp"
#include "GameState.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("Test Game State", "[model]") {
    GameState state = GameState();
    Move m1 = Move(0, PieceColor::RED, Rotation::ZERO, Vector2D(0, 0), Position(0, 0));
    WARN(state);
    state.performMove(m1);
    WARN(state);
}