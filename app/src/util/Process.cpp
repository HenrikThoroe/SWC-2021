#include <iostream>
#include <fstream>
#include <sstream> 
#include <algorithm>
#include <vector>

#include "Process.hpp"

namespace Util {

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

    uint64_t Process::rss() const {
        std::unordered_map<std::string, std::string> stats = readStats();

        if (stats.find("VmRSS") != stats.end()) {
            std::string rssStr = readStats().at("VmRSS");
            std::string value = rssStr.substr(0, rssStr.size() - 3);

            return std::stoi(value) * 1000;
        }

        return 0;
    }

    uint64_t Process::virtualMemory() const {
        std::unordered_map<std::string, std::string> stats = readStats();

        if (stats.find("VmSize") != stats.end()) {
            std::string rssStr = readStats().at("VmSize");
            std::string value = rssStr.substr(0, rssStr.size() - 3);

            return std::stoi(value) * 1000;
        }

        return 0;
    }

}