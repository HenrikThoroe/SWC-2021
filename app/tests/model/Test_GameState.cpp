#include "catch.hpp"
#include "GameState.hpp"

#include "Process.hpp"

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

    SECTION("Can Handle Last Player") {
        REQUIRE_THROWS(state.getLastPlayer());
        REQUIRE_THROWS(state.getLastPieceColor());

        state.performMove(nullptr);

        REQUIRE(state.getLastPlayer().color == PlayerColor::BLUE);
        REQUIRE(state.getLastPieceColor() == PieceColor::BLUE);

        state.performMove(nullptr);

        REQUIRE(state.getLastPlayer().color == PlayerColor::RED);
        REQUIRE(state.getLastPieceColor() == PieceColor::YELLOW);

        state.performMove(nullptr);

        REQUIRE(state.getLastPlayer().color == PlayerColor::BLUE);
        REQUIRE(state.getLastPieceColor() == PieceColor::RED);

        state.performMove(nullptr);

        REQUIRE(state.getLastPlayer().color == PlayerColor::RED);
        REQUIRE(state.getLastPieceColor() == PieceColor::GREEN);

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

                if (moves.size() <= 1) {
                    FAIL(state);
                }

                int index = rand() % moves.size();

                // Ignore skip moves, because hash does not take the current turn into account, but uniqueHash does
                while (moves[index] == nullptr) {
                    index = rand() % moves.size();
                }

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

    SECTION("Can Free Memory") {
        const Process p = Process();
        GameState state = GameState(20);
        std::vector<const Move*> moves {};
        int index;
        const uint64_t acceptance = 500'000; // Accept an unaccuracy of 500KB
        const auto fillMemory = [&state, &moves, &index] {
            for (int i = 0; i < 10000; ++i) {       
                for (int x = 0; x < 20; ++x) {
                    moves.clear();
                    state.assignPossibleMoves(moves);
                    if (moves.size() == 0) {
                        state.performMove(nullptr);
                    } else {
                        index = rand() % moves.size();
                        state.performMove(moves[index]);
                    }
                }

                for (int x = 0; x < 20; ++x) {
                    state.revertLastMove();
                }
            }
        };

        fillMemory();

        uint64_t firstRun = p.virtualMemory();

        state.freeMemory(1);

        fillMemory();

        uint64_t secondRun = p.virtualMemory();

        // No extra memory is used after it has been freed for reuse
        REQUIRE((secondRun + acceptance > firstRun && secondRun - acceptance < firstRun));
    }
}
