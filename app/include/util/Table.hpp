#pragma once

#include <inttypes.h>
#include <vector>
#include <string>
#include <iostream>

namespace Util::Print {

    /// A tool to easily construct tables for printing to the command line
    class Table {
        private:
            /// The number of columns
            uint8_t columns;

            /// The width of each column in printable characters
            uint8_t columnWidth;

            /// The content of each cell in each row including the header
            std::vector<std::vector<std::string>> rows;

        public:
            Table(uint8_t columns, uint8_t columnWidth);

            /// Adds a row for later serialization
            void addRow(std::vector<std::string> cells);

            friend std::ostream& operator << (std::ostream& os, const Table& table);        

    };

}
