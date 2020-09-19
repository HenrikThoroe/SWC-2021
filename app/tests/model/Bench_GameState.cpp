#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "GameState.hpp"

using namespace Model;

TEST_CASE("Bench Game State", "[benchmark]") {
    auto state = GameState(20);

    WARN(state.getPossibleMoves().size());

    BENCHMARK_ADVANCED("Move Calculation") (Catch::Benchmark::Chronometer meter) {
        for (int x = 0; x < 30; ++x) {
            std::vector<const Move*> moves;

            meter.measure([&moves, &state] {
                moves = state.getPossibleMoves();
            });

            if (moves.size() == 0) {
                FAIL(state);
            }

            int index = rand() % moves.size();

            state.performMove(moves[index]);
        }

        for (int x = 0; x < 30; ++x) {
            state.revertLastMove();
        }
    };

    BENCHMARK_ADVANCED("Perform Move") (Catch::Benchmark::Chronometer meter) {
        std::vector<const Move*> moves = state.getPossibleMoves();

        if (moves.size() == 0) {
            FAIL(state);
        }

        int index = rand() % moves.size();

        meter.measure([&state, &moves, &index] {
            state.performMove(moves[index]);
            state.revertLastMove();
        });
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
        for (int x = 0; x < 30; ++x) {
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

            state.performMove(moves[index]);
        }

        for (int x = 0; x < 30; ++x) {
            state.revertLastMove();
        }
    };

    BENCHMARK("Full Run Static") {
        std::vector<const Move*> moves {};

        for (int i = 0; i < 2000; ++i) {       
            for (int x = 0; x < 20; ++x) {
                moves.clear();
                state.assignPossibleMoves(moves);
                state.performMove(moves[0]);
            }

            for (int x = 0; x < 20; ++x) {
                state.revertLastMove();
            }
        }
    };

    BENCHMARK("Full Run Dynamic") {
        std::vector<const Move*> moves {};
        int index;

        for (int i = 0; i < 2000; ++i) {       
            for (int x = 0; x < 20; ++x) {
                moves.clear();
                state.assignPossibleMoves(moves);
                index = rand() % moves.size();
                state.performMove(*moves[index]);
            }

            for (int x = 0; x < 20; ++x) {
                state.revertLastMove();
            }
        }
    };

    BENCHMARK_ADVANCED("Hash") (Catch::Benchmark::Chronometer meter) {
        std::vector<const Move*> moves = state.getPossibleMoves();

        if (moves.size() == 0) {
            FAIL(state);
        }

        int index = rand() % moves.size();

        state.performMove(moves[index]);
        state.revertLastMove();

        meter.measure([&state] {
            return state.hash();
        });

        return moves;
    };
}