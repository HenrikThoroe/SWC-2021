#include <iostream>
#include <fstream>
#include <sstream> 
#include <algorithm>
#include <vector>

#include "Process.hpp"

namespace Util {

    //TODO: `Process::readStats` is using an inefficient but developer friendly way to read system information. If the impact of this method is too high, a more efficient solution should be implemented.
    std::unordered_map<std::string, std::string> Process::readStats() const {
        std::ifstream file("/proc/self/status");
        std::unordered_map<std::string, std::string> out;

        auto trim = [] (std::string& s) {
            s.erase(
                s.begin(), 
                std::find_if(
                    s.begin(), 
                    s.end(), 
                    [] (int ch) {
                        return !std::isspace(ch);
                    }
                )
            );

            s.erase(
                std::find_if(
                    s.rbegin(), 
                    s.rend(), 
                    [] (int ch) {
                        return !std::isspace(ch);
                    }
                ).base(), 
                s.end()
            );
        };

        if (file.is_open()) {
            std::string line;

            while (std::getline(file, line)) {
                std::istringstream linestream(line);
                std::vector<std::string> items;
                std::string buffer;

                while (std::getline(linestream, buffer, ':')) {
                    items.push_back(buffer);
                }

                if (items.size() == 2) {
                    trim(items[0]);
                    trim(items[1]);

                    out[items[0]] = items[1];
                }
            }
        }

        return out;
    }

    uint64_t Process::readEntry(const std::string& name, uint64_t factor, int suffixLength) const {
        std::unordered_map<std::string, std::string> stats = readStats();

        if (stats.find(name) != stats.end()) {
            std::string valStr = readStats().at(name);
            std::string value = valStr.substr(0, valStr.size() - suffixLength);

            return std::stoull(value) * factor;
        }

        return 0;
    }

    uint64_t Process::rss() const {
        return readEntry("VmRSS", 1000, 3);
    }

    uint64_t Process::virtualMemory() const {
        return readEntry("VmSize", 1000, 3);
    }

    void Process::printSystemStatus() const {
        std::cout << "--- System Status ---" << std::endl;
        std::cout << "RSS:            " << std::to_string(static_cast<double>(rss()) / 1000000) << " MB" << std::endl;
        std::cout << "Virtual Memory: " << std::to_string(static_cast<double>(virtualMemory()) / 1000000) << " MB" << std::endl;
        std::cout << "---------------------" << std::endl;
    }

}
