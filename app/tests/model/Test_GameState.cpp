#include "catch.hpp"
#include "GameState.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("Test Game State", "[model]") {
    GameState state = GameState(20);
    Move m1 = Move(20, PieceColor::BLUE, Rotation::ONEHALFPI, Vector2D(1, 1), Position(0, 0));

    SECTION("Switches Player and Piece Color") {
        REQUIRE(state.getCurrentPlayer().color == PlayerColor::BLUE);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::BLUE);
        REQUIRE(state.getTurn() == 0);

        state.performMove(nullptr);

        REQUIRE(state.getCurrentPlayer().color == PlayerColor::RED);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::YELLOW);
        REQUIRE(state.getTurn() == 1);

        state.performMove(nullptr);

        REQUIRE(state.getCurrentPlayer().color == PlayerColor::BLUE);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::RED);
        REQUIRE(state.getTurn() == 2);

        state.performMove(nullptr);

        REQUIRE(state.getCurrentPlayer().color == PlayerColor::RED);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::GREEN);
        REQUIRE(state.getTurn() == 3);

        state.performMove(nullptr);

        REQUIRE(state.getCurrentPlayer().color == PlayerColor::BLUE);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::BLUE);
        REQUIRE(state.getTurn() == 4);

        for (int i = 0; i < 4; ++i) {
            state.revertLastMove();
        }
    }

    SECTION("Validate Move") {
        Move m2 = Move(20, PieceColor::BLUE, Rotation::PI, Vector2D(1, 1), Position(0, 0));

        REQUIRE(state.canBeDeployed(m1));
        REQUIRE_FALSE(state.canBeDeployed(m2));
    }

    state.performMove(&m1);

    SECTION("Can Perform Move") {
        REQUIRE(state.getTurn() == 1);
        REQUIRE(state.getCurrentPlayer().color == PlayerColor::RED);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::YELLOW);
    }

    state.revertLastMove();

    uint64_t initialHash = state.hash();
    state.performMove(nullptr);

    SECTION("Can Skip a Move") {
        REQUIRE(state.getTurn() == 1);
        REQUIRE(state.getCurrentPlayer().color == PlayerColor::RED);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::YELLOW);
        REQUIRE(state.hash() == initialHash);
    }

    state.revertLastMove();

    SECTION("Can Revert Move") {
        REQUIRE(state.getTurn() == 0);
        REQUIRE(state.getCurrentPlayer().color == PlayerColor::BLUE);
        REQUIRE(state.getCurrentPieceColor() == PieceColor::BLUE);
    }

    SECTION("Can Create and Revert Hashes") {
        std::stack<uint64_t> hashes {};

        for (int x = 0; x < 30; ++x) {
            std::vector<const Move*> moves = state.getPossibleMoves();

            if (moves.size() == 0) {
                FAIL(state);
            }

            int index = rand() % moves.size();

            state.performMove(moves[index]);
            hashes.push(state.hash());
        }

        for (int x = 0; x < 30; ++x) {
            REQUIRE(hashes.top() == state.hash());
            hashes.pop();
            state.revertLastMove();
        }
    }

    SECTION("Has no Collisions") {
        std::unordered_map<uint64_t, std::bitset<808>> map {};

        for (int it = 0; it < 10000; ++it) {
            for (int x = 0; x < 25; ++x) {
                std::vector<const Move*> moves = state.getPossibleMoves();

                if (moves.size() == 0) {
                    FAIL(state);
                }

                int index = rand() % moves.size();

                state.performMove(moves[index]);
                
                if (map.find(state.hash()) == map.end()) {
                    map[state.hash()] = state.uniqueHash();
                } else {
                    INFO(state);
                    INFO(state.hash());
                    INFO(map[state.hash()]);
                    INFO(state.uniqueHash());
                    REQUIRE(map[state.hash()] == state.uniqueHash());
                }
            }

            for (int x = 0; x < 25; ++x) {
                state.revertLastMove();
            }
        }
    }
}
