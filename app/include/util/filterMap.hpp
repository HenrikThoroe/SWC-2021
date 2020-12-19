#pragma once 

#include <functional>
#include "robin_map.hpp"

namespace Util {

    template<typename K, typename V>
    void filterMap(tsl::robin_map<K, V>& map, const std::function<bool(const K&, const V&)>& callback) {
        auto it = map.begin();

        while (it != map.end()) {
            if (callback(it->first, it->second)) {
                it = map.erase(it);
            } else {
                ++it;
            }
        }
    }

}
