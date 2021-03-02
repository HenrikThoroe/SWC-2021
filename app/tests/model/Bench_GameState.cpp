#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "GameState.hpp"

#include "Process.hpp"

using namespace Model;

TEST_CASE("Bench Game State", "[benchmark]") {
    auto state = GameState(20);

    WARN(state.getPossibleMoves().size());

    BENCHMARK_ADVANCED("Move Calculation") (Catch::Benchmark::Chronometer meter) {
        std::stack<const Move*> performedMoves;

        for (int x = 0; x < 30; ++x) {
            std::vector<const Move*> moves;

            meter.measure([&moves, &state] {
                moves = state.getPossibleMoves();
            });

            if (moves.size() == 0) {
                state.performMove(nullptr);
                performedMoves.push(nullptr);
            } else {
                int index = rand() % moves.size();
                state.performMove(moves[index]);
                performedMoves.push(moves[index]);
            }
        }

        for (int x = 0; x < 30; ++x) {
            state.revertMove(performedMoves.top());
            performedMoves.pop();
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
            state.revertMove(moves[index]);
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
        std::stack<const Move*> performedMoves;

        for (int x = 0; x < 30; ++x) {
            std::vector<const Move*> moves = state.getPossibleMoves();

            if (moves.size() == 0) {
                state.performMove(nullptr);
                performedMoves.push(nullptr);
                continue;
            }

            meter.measure([&state, &moves] {
                return state.canBeDeployed(moves[moves.size() - 1]);
            });

            int index = rand() % moves.size();

            state.performMove(moves[index]);
            performedMoves.push(moves[index]);
        }

        for (int x = 0; x < 30; ++x) {
            state.revertMove(performedMoves.top());
            performedMoves.pop();
        }
    };

    BENCHMARK("Full Run Static") {
        std::vector<const Move*> moves {};

        const auto bench = [&state, &moves](int depth)->void {
            auto bench_imp = [&state, &moves](int depth, auto& bench_ref) mutable {
                if (depth == 0) {
                    return;
                }

                moves.clear();
                state.assignPossibleMoves(moves);
                
                const Move* move = nullptr;
                if (moves.size() > 0) {
                    move = moves[0];
                }

                state.performMove(move);
                bench_ref(depth - 1, bench_ref);
                state.revertMove(move);
            };
            return bench_imp(depth, bench_imp);
        };

        for (int i = 0; i < 100; ++i) {       
            bench(50);
        }
    };

    BENCHMARK("Full Run Dynamic") {
        std::vector<const Move*> moves {};
        int index;

        const auto bench = [&state, &moves, &index](int depth)->void {
            auto bench_imp = [&state, &moves, &index](int depth, auto& bench_ref) mutable {
                if (depth == 0) {
                    return;
                }

                moves.clear();
                state.assignPossibleMoves(moves);
                
                const Move* move = nullptr;
                if (moves.size() > 0) {
                    index = rand() % moves.size();
                    move = moves[index];
                }

                state.performMove(move);
                bench_ref(depth - 1, bench_ref);
                state.revertMove(move);
            };
            return bench_imp(depth, bench_imp);
        };

        for (int i = 0; i < 100; ++i) {       
            bench(50);
        }
    };

    BENCHMARK_ADVANCED("Hash") (Catch::Benchmark::Chronometer meter) {
        std::vector<const Move*> moves = state.getPossibleMoves();

        if (moves.size() == 0) {
            FAIL(state);
        }

        int index = rand() % moves.size();

        state.performMove(moves[index]);
        state.revertMove(moves[index]);

        meter.measure([&state] {
            return state.hash();
        });

        return moves;
    };

    BENCHMARK_ADVANCED("Eval") (Catch::Benchmark::Chronometer meter) {
        std::stack<const Move*> performedMoves;
        std::vector<const Move*> moves;
        int index;

        for (int x = 0; x < 20; ++x) {
            moves.clear();
            state.assignPossibleMoves(moves);

            if (moves.size() == 0) {
                state.performMove(nullptr);
                performedMoves.push(nullptr);
            } else {
                index = rand() % moves.size();
                state.performMove(moves[index]);
                performedMoves.push(moves[index]);
            }

            meter.measure([&state] {
                return state.evaluate(PlayerColor::BLUE);
            });
        }

        for (int x = 0; x < 20; ++x) {
            state.revertMove(performedMoves.top());
            performedMoves.pop();
        }
    };

    BENCHMARK_ADVANCED("Memory Cleanup") (Catch::Benchmark::Chronometer meter) {
        std::stack<const Move*> performedMoves;
        std::vector<const Move*> moves {};
        int index;
        const Util::Process p = Util::Process();
        uint64_t vm = p.virtualMemory();

        // Virtual memory < 1GB
        while (vm < 1'000'000'000) {
            for (int x = 0; x < 20; ++x) {
                moves.clear();
                state.assignPossibleMoves(moves);
                if (moves.size() == 0) {
                    state.performMove(nullptr);
                    performedMoves.push(nullptr);
                } else {
                    index = rand() % moves.size();
                    state.performMove(moves[index]);
                    performedMoves.push(moves[index]);
                }
            }

            for (int x = 0; x < 20; ++x) {
                state.revertMove(performedMoves.top());
                performedMoves.pop();
            }

            vm = p.virtualMemory();
        }

        meter.measure([&state] {
            state.freeMemory(1);
        });
    };
}
