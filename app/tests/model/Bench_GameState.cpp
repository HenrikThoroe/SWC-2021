#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "GameState.hpp"

using namespace Model;

TEST_CASE("Bench Game State", "[benchmark]") {
    auto state = GameState();

    WARN(state.getPossibleMoves().size());

    BENCHMARK_ADVANCED("Move Calculation") (Catch::Benchmark::Chronometer meter) {
        for (int x = 0; x < 35; ++x) {
            std::vector<const Move*> moves;

            meter.measure([&moves, &state] {
                moves = state.getPossibleMoves();
            });

            if (moves.size() == 0) {
                FAIL(state);
            }

            int index = rand() % moves.size();

            state.performMove(*moves[index]);
        }

        for (int x = 0; x < 35; ++x) {
            state.revertLastMove();
        }
    };

    BENCHMARK("Get Possible Moves") {
        return state.getPossibleMoves();
    };

    BENCHMARK_ADVANCED("Assign Possible Moves") (Catch::Benchmark::Chronometer meter) {
        std::vector<const Move*> out {};
        meter.measure([&out, &state] {
            state.assignPossibleMoves(out);
        });
        return out;
    };

    BENCHMARK_ADVANCED("Can Be Deployed") (Catch::Benchmark::Chronometer meter) {
        for (int x = 0; x < 35; ++x) {
            std::vector<const Move*> moves = state.getPossibleMoves();

            if (moves.size() == 0) {
                FAIL(state);
            }

            meter.measure([&state, &moves] {
                bool res = true;
                for (const Move* move : moves) {
                    res = res && state.canBeDeployed(move);
                } 

                return res;
            });

            int index = rand() % moves.size();

            state.performMove(*moves[index]);
        }

        for (int x = 0; x < 35; ++x) {
            state.revertLastMove();
        }
    };
}