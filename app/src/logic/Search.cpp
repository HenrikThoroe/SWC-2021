#include "Search.hpp"

namespace Logic {

    SearchResult::SearchResult(const Model::Move* move, const int score) : move(move), score(score) {}

    Search::Search(Model::GameState& state, const Model::PlayerColor& player) : state(state), player(player), selectedMove(nullptr) {}

    SearchResult Search::find() {
        const int score = alphaBeta();
        return SearchResult(selectedMove, score);
    }

    int Search::alphaBeta() {
        maxDepth = 3;
        return max(INT_MIN, INT_MAX, 3);
    }

    int Search::min(int alpha, int beta, int depth) {
        if (depth == 0 || state.isGameOver()) {
            return state.evaluate(player);
        }

        int min = beta;
        std::vector<const Model::Move*> moves;

        state.assignPossibleMoves(moves);

        for (const Model::Move* move : moves) {
            state.performMove(move);
            int score = max(alpha, min, depth - 1);
            state.revertLastMove();

            if (score < min) {
                min = score;

                if (min <= alpha) {
                    break;
                }
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

        for (const Model::Move* move : moves) {
            state.performMove(move);
            int score = min(max, beta, depth - 1);
            state.revertLastMove();

            if (score > max) {
                max = score;
                if (depth == maxDepth) {
                    selectedMove = move;
                }
                if (max >= beta) {
                    break;
                }
            }
        }

        return max;
    }

}
