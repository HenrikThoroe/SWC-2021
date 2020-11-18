#include "Search.hpp"
#include "Table.hpp"
#include "stringTools.hpp"

namespace Logic {

    SearchResult::SearchResult(const Model::Move* move, const int score) : move(move), score(score) {}

    Search::Search(Model::GameState& state, const Model::PlayerColor& player) : state(state), player(player), selectedMove(nullptr), clock(), searchedNodes(0) {}

    SearchResult Search::find() {
        reset();
        int score;

        do {
            score = alphaBeta();
            maxDepth += 1;
        } while (!timedOut() && score != Constants::WIN_POINTS && score != Constants::LOSE_POINTS);

        lastScore = score;

        return SearchResult(selectedMove, score);
    }

    void Search::log() const {
        const int64_t elapsed = getElpasedTime().count();
        const double nodesPerNs = static_cast<double>(searchedNodes) / static_cast<double>(elapsed);
        const double nodesPerMs = nodesPerNs * 1000000;
        const double nodesPerS = nodesPerMs * 1000;
        double cutoffRatio = 0;

        if (searchedNodes > 0) {
            cutoffRatio = static_cast<double>(alphaCutoffs + betaCutoffs) / static_cast<double>(searchedNodes);
        }

        Util::Print::Table table = Util::Print::Table(8, 25);
        table.addRow({ "Depth", "Searched Nodes", "Elpased Time", "Nodes per Millisecond", "Nodes per Second", "Alpha Cutoffs", "Beta Cutoffs", "Cutoff Ratio" });
        table.addRow({
            Util::Print::Text::formatInt(maxDepth),
            Util::Print::Text::formatInt(searchedNodes),
            Util::Print::Text::formatTime(elapsed, Util::Print::Text::TimeUnit::NS),
            Util::Print::Text::formatDouble(nodesPerMs),
            Util::Print::Text::formatDouble(nodesPerS),
            Util::Print::Text::formatInt(alphaCutoffs),
            Util::Print::Text::formatInt(betaCutoffs),
            Util::Print::Text::formatDouble(cutoffRatio * 100, 2) + "%"
        });

        std::cout << std::endl << std::endl << Util::Print::Text::repeat('*', 3) << " Search Statistics " << Util::Print::Text::repeat('*', 150) << std::endl << std::endl;
        std::cout << Util::Print::Text::bold("Selected Move: ");

        if (selectedMove == nullptr) {
            std::cout << "Skip Move";
        } else {
            std::cout << *selectedMove;
        }

        std::cout << std::endl << Util::Print::Text::bold("Score: ");
        std::cout << lastScore;

        std::cout << std::endl << std::endl;

        std::cout << table;
        std::cout << std::endl << Util::Print::Text::repeat('*', 172) << std::endl << std::endl << std::endl;
    }

    void Search::reset() {
        startTime = clock.now();
        searchedNodes = 0;
        alphaCutoffs = 0;
        betaCutoffs = 0;
        maxDepth = 1;
        selectedMove = nullptr;
        invalidColors.reset();
        lastScore = 0;
    }

    std::chrono::high_resolution_clock::duration Search::getElpasedTime() const {
        return clock.now() - startTime;
    }

    inline bool Search::timedOut() const {
        return getElpasedTime().count() >= 1500000000;
    }

    void Search::sortMoves(std::vector<const Model::Move*>& moves) const {
        const Model::Move* selectedMove = this->selectedMove;

        auto compareDescending = [&selectedMove] (const Model::Move* lhs, const Model::Move* rhs) {
            if (lhs == nullptr) {
                return false;
            }

            if (rhs == nullptr) {
                return true;
            }

            if (lhs == selectedMove) {
                return true;
            }

            if (rhs == selectedMove) {
                return false;
            }

            return lhs->pieceId > rhs->pieceId;
        };

        std::sort(moves.begin(), moves.end(), compareDescending);
    }

    int Search::alphaBeta() {
        return max(INT_MIN, INT_MAX, maxDepth);
    }

    int Search::min(int alpha, int beta, int depth) {
        if (depth == 0 || state.isGameOver()) {
            return state.evaluate(player);
        }

        int min = beta;
        std::vector<const Model::Move*> moves;

        state.assignPossibleMoves(moves);

        if (moves.size() == 1) {
            invalidColors[static_cast<uint8_t>(state.getCurrentPieceColor()) - 1] = true;
        }

        if (invalidColors.count() == 4) {
            return state.evaluate(player, true);
        }

        sortMoves(moves);

        for (const Model::Move* move : moves) {
            state.performMove(move);
            int score = max(alpha, min, depth - 1);
            searchedNodes += 1;
            state.revertLastMove();

            if (score < min) {
                min = score;

                if (min <= alpha) {
                    alphaCutoffs += 1;
                    break;
                }
            }

            if (timedOut()) {
                break;
            }
        }

        return min;
    }

    int Search::max(int alpha, int beta, int depth) {
        if (depth == 0 || state.isGameOver()) {
            return state.evaluate(player);
        }

        int max = alpha;
        std::vector<const Model::Move*> moves;

        state.assignPossibleMoves(moves);

        if (moves.size() == 1) {
            invalidColors[static_cast<uint8_t>(state.getCurrentPieceColor()) - 1] = true;
        }

        if (invalidColors.count() == 4) {
            return state.evaluate(player, true);
        }

        sortMoves(moves);

        for (const Model::Move* move : moves) {
            state.performMove(move);
            int score = min(max, beta, depth - 1);
            searchedNodes += 1;
            state.revertLastMove();

            if (score > max) {
                max = score;
                if (depth == maxDepth) {
                    selectedMove = move;
                }
                if (max >= beta) {
                    betaCutoffs += 1;
                    break;
                }
            }

            if (timedOut()) {
                break;
            }
        }

        return max;
    }

}
