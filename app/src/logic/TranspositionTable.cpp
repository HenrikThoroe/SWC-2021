#include "TranspositionTable.hpp"
#include "filterMap.hpp"

namespace Logic {

    TTEntry::TTEntry() : hash(0), evaluation(0), type(TTEntryType::EXACT), depth(0), move(nullptr), turn(0) {}
    TTEntry::TTEntry(uint64_t hash, int evaluation, TTEntryType type, int depth, uint8_t turn, const Model::Move* move) : hash(hash), evaluation(evaluation), type(type), depth(depth), move(move), turn(turn) {}
    TTEntry::TTEntry(const TTEntry& other) : hash(other.hash), evaluation(other.evaluation), type(other.type), depth(other.depth), move(other.move), turn(other.turn) {}
    TTEntry::TTEntry(TTEntry* other) : hash(other->hash), evaluation(other->evaluation), type(other->type), depth(other->depth), move(other->move), turn(other->turn) {}

    TTEntry& TTEntry::operator = (const TTEntry& other) {
        this->hash = other.hash;
        this->evaluation = other.evaluation;
        this->type = other.type;
        this->depth = other.depth;
        this->move = other.move;
        this->turn = other.turn;

        return *this;
    }

    TranspositionTable::TranspositionTable() : hashMap() {
        hashMap.reserve(3'000'000); 
    }

    bool TranspositionTable::has(const uint64_t& key) const {
        return hashMap.contains(key);
    }

    TTEntry& TranspositionTable::get(const uint64_t& key) {
        return hashMap[key];
    }

    void TranspositionTable::set(const TTEntry& entry) {
        hashMap[entry.hash] = entry;
    }

    int TranspositionTable::size() const {
        return hashMap.size();
    }

    void TranspositionTable::freeMemory(int currentTurn) {
        const std::function<bool(const uint64_t&, const TTEntry&)> filter = [&currentTurn] (const uint64_t& key, const TTEntry& entry) {
            return entry.turn < currentTurn;
        };

        Util::filterMap(hashMap, filter);
    }

}
