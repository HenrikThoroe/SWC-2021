#pragma once

#include <inttypes.h>
#include "robin_map.hpp"

#include "Move.hpp"

namespace Logic {

    enum class TTEntryType: uint8_t {
        EXACT,
        UPPER_BOUND,
        LOWER_BOUND
    };

    struct TTEntry {
        TTEntry(uint64_t hash, int evaluation, TTEntryType type, int depth, Model::Move* move);
        TTEntry(const TTEntry& other);
        TTEntry(TTEntry* other);

        uint64_t hash;

        int evaluation;

        int depth;

        Model::Move* move;

        TTEntryType type;

        TTEntry& operator = (const TTEntry& other);
    };

    class TranspositionTable {
        private:
            tsl::robin_map<uint64_t, TTEntry> hashMap;
        public:
            TranspositionTable();
            TranspositionTable(TranspositionTable* other) = delete;
            TranspositionTable(TranspositionTable& other) = delete;

            bool has(const uint64_t& key) const;
            const TTEntry& get(const uint64_t& key);
            void set(const TTEntry& entry);
            int size() const;
    };

}
