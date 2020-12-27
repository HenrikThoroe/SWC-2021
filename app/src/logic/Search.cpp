#include "Search.hpp"
#include "Table.hpp"
#include "stringTools.hpp"
#include "constants.hpp"

namespace Logic {

    SearchResult::SearchResult(const Model::Move* move, const int score) : move(move), score(score) {}

    Search::Search(Model::GameState& state, const Model::PlayerColor& player) : state(state), player(player), selectedMove(nullptr), clock(), searchedNodes(0), table(), tableHits(0), invalidMask() {}

    SearchResult Search::find() {
        reset();
        int score;

        do {
            score = alphaBeta();
            maxDepth += 1;
        } while (!timedOut() && state.getTurn() + (maxDepth - 1) < 100);

        lastScore = score;

        return SearchResult(selectedMove, score);
    }

    void Search::setInvalidColors(const std::vector<Model::PieceColor>* const valid) {
        invalidMask = 0b1111;

        for (const Model::PieceColor& color : *valid) {
            invalidMask[static_cast<uint32_t>(color) - 1] = 0;
        }
    }

    void Search::clean() {
        table.freeMemory(state.getTurn());
    }

    void Search::log() const {
        const int64_t elapsed = getElpasedTime().count();
        const double nodesPerNs = static_cast<double>(searchedNodes) / static_cast<double>(elapsed);
        const double nodesPerS = nodesPerNs * 1000000000;
        double cutoffRatio = 0;
        double hitRatio = 0;
        double branchingFactor = 0;

        if (expandedNodes != 0) {
            branchingFactor = static_cast<double>(searchedChildren) / static_cast<double>(expandedNodes);
        }

        if (searchedNodes > 0) {
            cutoffRatio = static_cast<double>(alphaCutoffs + betaCutoffs) / static_cast<double>(searchedNodes);
            hitRatio = static_cast<double>(tableHits) / static_cast<double>(searchedNodes);
        }

        Util::Print::Table table = Util::Print::Table(11, 21);
        table.addRow({ "Depth", "Searched Nodes", "Elpased Time", "Nodes per Second", "Alpha Cutoffs", "Beta Cutoffs", "Cutoff Ratio", "Branching", "Table Size", "Table Hits", "Hit Ratio" });
        table.addRow({
            Util::Print::Text::formatInt(maxDepth - 1),
            Util::Print::Text::formatInt(searchedNodes),
            Util::Print::Text::formatTime(elapsed, Util::Print::Text::TimeUnit::NS),
            Util::Print::Text::formatDouble(nodesPerS),
            Util::Print::Text::formatInt(alphaCutoffs),
            Util::Print::Text::formatInt(betaCutoffs),
            Util::Print::Text::formatDouble(cutoffRatio * 100, 2) + "%",
            Util::Print::Text::formatDouble(branchingFactor),
            Util::Print::Text::formatInt(this->table.size()),
            Util::Print::Text::formatInt(tableHits),
            Util::Print::Text::formatDouble(hitRatio * 100, 2) + "%"
        });

        std::cout << '\n' << '\n' << Util::Print::Text::repeat('*', 3) << " Search Statistics " << Util::Print::Text::repeat('*', 150) << '\n' << '\n';
        std::cout << Util::Print::Text::bold("Selected Move: ");

        if (selectedMove == nullptr) {
            std::cout << "Skip Move";
        } else {
            std::cout << *selectedMove;
        }

        std::cout << '\n' << Util::Print::Text::bold("Score: ");

        if (lastScore >= Constants::WIN_POINTS) {
            std::cout << Util::Print::Text::color("WIN", Util::Print::Text::TextColor::GREEN);
        } else if (lastScore <= Constants::LOSE_POINTS) {
            std::cout << Util::Print::Text::color("LOSE", Util::Print::Text::TextColor::RED);
        } else {
            std::cout << lastScore;
        }

        std::cout << '\n' << '\n';

        std::cout << table;
        std::cout << '\n' << Util::Print::Text::repeat('*', 172) << '\n' << '\n' << std::endl;
    }

    void Search::reset() {
        startTime = clock.now();
        searchedNodes = 0;
        alphaCutoffs = 0;
        betaCutoffs = 0;
        maxDepth = 1;
        selectedMove = nullptr;
        lastScore = 0;
        tableHits = 0;
        expandedNodes = 0;
        searchedChildren = 0;
    }

    std::chrono::high_resolution_clock::duration Search::getElpasedTime() const {
        return clock.now() - startTime;
    }

    bool Search::timedOut() const {
        return getElpasedTime().count() >= Constants::SEARCH_TIMEOUT;
    }

    bool Search::fetchEntry(int& exact, int& alpha, int& beta, const Model::Move*& bestMove, int depth) {
        if (table.has(state.hash())) {
            const TTEntry& entry = table.get(state.hash());

            if (entry.depth >= depth && state.hash() == entry.hash && entry.turn < 100) {
                tableHits += 1;

                bestMove = entry.move;

                switch (entry.type) {
                    case TTEntryType::EXACT:
                        exact = entry.evaluation;
                        return depth != maxDepth;

                    case TTEntryType::UPPER_BOUND:
                        alpha = std::min(entry.evaluation, alpha);
                        break;

                    case TTEntryType::LOWER_BOUND:
                        beta = std::max(entry.evaluation, beta);
                        break;
                }

                if (alpha >= beta) {
                    betaCutoffs += 1;
                    exact = entry.evaluation;
                    return true;
                }

                return false;
            }
        }

        return false;
    }

    void Search::setEntry(int score, int depth, const TTEntryType& type, const Model::Move* bestMove) {
        // Indicates if the current state is already in the table and evaluated up to a higher depth
        const bool hasBetterEntry = table.has(state.hash()) && table.get(state.hash()).depth > depth;

        // A node at turn >= 100 is always a terminal node. 
        // But the same state can be a non terminal node at lower depth.
        // Therefore storing the node with WIN / LOSE points an reading at depth < 100 would lead to wrong evaluation
        const bool isOverTimeNode = state.getTurn() >= 100;

        if (hasBetterEntry || isOverTimeNode) {
            return;
        }

        const TTEntry entry = TTEntry(state.hash(), score, type, depth, state.getTurn(), bestMove);
        table.set(entry);
    }

    void Search::insertKiller(const Model::Move* move) {
        const uint8_t turn = state.getTurn();
        static uint64_t counter = 0;

        if (killerTable[turn].size() < 4) {
            killerTable[turn].push_back(move);
        } else {
            for (const Model::Move* stored : killerTable[turn]) {
                if (stored == move) {
                    return;
                }
            }

            killerTable[turn][counter % 4] = move;
            counter += 1;
        }
    }

    void Search::sortMoves(std::vector<const Model::Move*>& moves, const Model::Move* hashMove) const {
        auto compareDescending = [&hashMove, this] (const Model::Move* lhs, const Model::Move* rhs) {
            if (lhs == nullptr) {
                return false;
            }

            if (rhs == nullptr) {
                return true;
            }

            if (lhs == hashMove) {
                return true;
            }

            if (rhs == hashMove) {
                return false;
            }

            for (const Model::Move* killer : killerTable[state.getTurn()]) {
                if (lhs == killer) {
                    return true;
                }

                if (rhs == killer) {
                    return false;
                }
            }

            return lhs->pieceId > rhs->pieceId;
        };

        std::sort(moves.begin(), moves.end(), compareDescending);
    }

    int Search::alphaBeta(int alpha, int beta) {
        return max(alpha, beta, maxDepth);
    }

    bool Search::prepareSearch(int& alpha, int& beta, int depth, std::vector<const Model::Move*>& moves, int& nodeValue, bool& didInvalidate) {
        int exact = 0;
        const Model::Move* bestMove = nullptr;
        bool isExact = fetchEntry(exact, alpha, beta, bestMove, depth);

        searchedNodes += 1;

        if (isExact) {
            nodeValue = exact;
            return true;
        }

        if (depth == 0 || state.isGameOver()) {
            nodeValue = state.evaluate(player, &invalidMask);
            return true;
        }

        state.assignPossibleMoves(moves);

        int movesCount = moves.size();
        size_t colorId = static_cast<uint32_t>(state.getCurrentPieceColor()) - 1;
        didInvalidate = movesCount <= 1 && !invalidMask[colorId];

        if (didInvalidate) {
            invalidMask[colorId] = 1;
        }

        if (invalidMask.count() == 4) {
            nodeValue = state.evaluate(player, &invalidMask);
            invalidMask[colorId] = 0;
            return true;
        }

        sortMoves(moves, bestMove);

        // Remove skip move from list if other moves are available
        if (movesCount > 1 && state.getTurn() > 3) {
            moves.pop_back();
        }

        expandedNodes += 1;

        return false;
    }

    void Search::finishSearch(int alpha, int beta, int score, int depth, const Model::Move* bestMove, bool didInvalidate) {
        size_t colorId = static_cast<uint32_t>(state.getCurrentPieceColor()) - 1;

        if (didInvalidate) {
            invalidMask[colorId] = 0;
        }

        if (score <= alpha) {
            // No move was found which is better than alpha. No reason to perform it.
            setEntry(score, depth, TTEntryType::UPPER_BOUND, bestMove);
        } else if (score >= beta) {
            // Only a move which is better than beta was found. Therefore the opponent will not allow this move
            setEntry(score, depth, TTEntryType::LOWER_BOUND, bestMove);
        } else {
            // An exact move was found. 
            setEntry(score, depth, TTEntryType::EXACT, bestMove);
        }
    }

    int Search::min(int alpha, int beta, int depth) {
        int exact = 0;
        std::vector<const Model::Move*> moves;
        bool didBecomeInvalid;

        bool shouldReturn = prepareSearch(alpha, beta, depth, moves, exact, didBecomeInvalid);

        if (shouldReturn) {
            return exact;
        }

        int min = beta;
        const Model::Move* selected = nullptr;

        for (const Model::Move* move : moves) {
            state.performMove(move);
            int score = max(alpha, min, depth - 1);
            state.revertLastMove();
            searchedChildren += 1;

            if (score < min) {
                min = score;

                if (min <= alpha) {
                    alphaCutoffs += 1;
                    break;
                }

                selected = move;
            }

            if (timedOut()) {
                break;
            }
        }

        finishSearch(alpha, beta, min, depth, selected, didBecomeInvalid);

        return min;
    }

    int Search::max(int alpha, int beta, int depth) {
        int exact = 0;
        std::vector<const Model::Move*> moves;
        bool didBecomeInvalid;

        bool shouldReturn = prepareSearch(alpha, beta, depth, moves, exact, didBecomeInvalid);

        if (shouldReturn) {
            return exact;
        }

        int max = alpha;
        const Model::Move* selected = nullptr;

        for (const Model::Move* move : moves) {
            state.performMove(move);
            int score = min(max, beta, depth - 1);
            state.revertLastMove();
            searchedChildren += 1;

            if (score > max) {
                max = score;
                selected = move;
                if (depth == maxDepth) {
                    selectedMove = move;
                }
                if (max >= beta) {
                    betaCutoffs += 1;
                    insertKiller(move);
                    break;
                }
            } 

            if (timedOut()) {
                break;
            }
        }

        #ifdef DEBUG
        // Check if search failed because alpha is equal to the maximum score at root level.
        // Should not happen since the transposition table bug was fixed
        if (max == alpha && depth == maxDepth) {
            assert(selectedMove != nullptr);
        }
        #endif

        finishSearch(alpha, beta, max, depth, selected, didBecomeInvalid);

        return max;
    }

}
