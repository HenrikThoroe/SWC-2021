#pragma once

#include <inttypes.h>
#include "robin_map.hpp"

#include "Move.hpp"

namespace Logic {

    /// Flags to indicate which type of node is stored.
    enum class TTEntryType: uint8_t {
        /// The exact value of the node. All subnodes have been searched
        EXACT,  

        /// The upper bound for the node. Subnodes have to be worse than this value
        UPPER_BOUND,

        /// The lower bound for the node. Subnodes have to be better than this value
        LOWER_BOUND
    };

    /// A data structure to store all required information for an entry of the transposition table
    struct TTEntry {
        /// Default constructor is required for creating entries in hash map
        TTEntry();

        /// Inits the entry with values for each field
        TTEntry(uint64_t hash, int evaluation, TTEntryType type, int depth, uint8_t turn, const Model::Move* move);

        /// Copy constructor to move entries when for example a rehash and bucket rearangement is required
        TTEntry(const TTEntry& other);

        /// Copy constructor to move entries when for example a rehash and bucket rearangement is required
        TTEntry(TTEntry* other);

        /// The hash identifier of the entry to detect key collisions of the hash map
        uint64_t hash;

        /// The evaluation of the stored node
        int evaluation;

        /// The depth at which the node was found
        int depth;

        /// The turn of the node. Useful for smart entry deletion
        uint8_t turn;

        /// The associated move of the node or `nullptr` if not at max depth.
        const Model::Move* move;

        /// The type of the node to determine if the score is exact or a bound
        TTEntryType type;

        TTEntry& operator = (const TTEntry& other);
    };

    /// A wrapper around a simple hash map designed to manage transpositions
    class TranspositionTable {
        private:

            /// Internal storage for all entries
            tsl::robin_map<uint64_t, TTEntry> hashMap;

        public:

            TranspositionTable();
            TranspositionTable(TranspositionTable* other) = delete;
            TranspositionTable(TranspositionTable& other) = delete;

            /// Returns true if `key` is stored
            bool has(const uint64_t& key) const;

            /**
             * @brief Returns a modifiable reference to the entry associated with `key`
             * @warning If `key` is not in the hash map undefined behaviour or a segmentation fault can occur
             */
            TTEntry& get(const uint64_t& key);

            /// Adds or updates the entry
            void set(const TTEntry& entry);

            /// The number of stored entries
            int size() const;

            /**
             * @brief Erases old entries from the table. The freed space will be reused by upcoming entries.
             * @param currentTurn The current turn on the game state. Entries older than that will be deleted.
             */
            void freeMemory(int currentTurn);
    };

}
