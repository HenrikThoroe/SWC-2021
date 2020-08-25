#pragma once 

#include <inttypes.h>
#include <unordered_map>
#include <string>

namespace Util {

    class Process {
        private:
            /// Reads process information from "/proc/self/status"
            std::unordered_map<std::string, std::string> readStats() const;

        public:
            /// Returns the currently used resident set size (physically used RAM). 
            uint64_t rss() const;

            /// Returns the currently used virtual memory (sum of RAM, CPU Cache, Swap, ...).
            uint64_t virtualMemory() const;
    };

}