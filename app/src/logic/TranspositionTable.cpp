#include "TranspositionTable.hpp"

namespace Logic {

    TTEntry::TTEntry(uint64_t hash, int evaluation, TTEntryType type, int depth, Model::Move* move) : hash(hash), evaluation(evaluation), type(type), depth(depth), move(move) {}
    TTEntry::TTEntry(const TTEntry& other) : hash(other.hash), evaluation(other.evaluation), type(other.type), depth(other.depth), move(other.move) {}
    TTEntry::TTEntry(TTEntry* other) : hash(other->hash), evaluation(other->evaluation), type(other->type), depth(other->depth), move(other->move) {}

    TTEntry& TTEntry::operator = (const TTEntry& other) {
        this->hash = other.hash;
        this->evaluation = other.evaluation;
        this->type = other.type;
        this->depth = other.depth;
        this->move = other.move;

        return *this;
    }

    TranspositionTable::TranspositionTable() : hashMap() {
        hashMap.reserve(3000000); 
    }

    bool TranspositionTable::has(const uint64_t& key) const {
        return hashMap.contains(key);
    }

    const TTEntry& TranspositionTable::get(const uint64_t& key) {
        return hashMap.at(key);
    }

    void TranspositionTable::set(const TTEntry& entry) {
        hashMap.insert(std::make_pair(entry.hash, entry));
    }

    int TranspositionTable::size() const {
        return hashMap.size();
    }

}
