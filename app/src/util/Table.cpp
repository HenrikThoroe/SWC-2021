#include "Table.hpp"
#include "stringTools.hpp"

namespace Util::Print {

    Table::Table(uint8_t columns, uint8_t columnWidth) : columns(columns), columnWidth(columnWidth), rows() {}

    void Table::addRow(std::vector<std::string> cells) {
        rows.push_back(cells);
    }

    std::ostream& operator << (std::ostream& os, const Table& table) {
        for (int r = 0; r < table.rows.size(); ++r) {
            const std::vector<std::string>& row = table.rows[r];

            if (r > 0) {
                os << Text::repeat('-', table.columns * table.columnWidth + (table.columns - 1) * 3) << std::endl;
            }

            for (int i = 0; i < table.columns; ++i) {
                if (i > 0) {
                    os << " | ";
                }

                if (r == 0) {
                    os << "\033[1;37m";
                }

                if (row.size() > i) {
                    if (r == 0) {
                        os << Text::fixedWidth(row[i], table.columnWidth, Text::TextAlignment::CENTER);
                    } else {
                        os << Text::fixedWidth(row[i], table.columnWidth, Text::TextAlignment::RIGHT);
                    }
                } else {
                    os << Text::repeat(' ', table.columnWidth);
                }

                if (r == 0) {
                    os << "\033[0m";
                }
            }

            os << std::endl;
        }

        return os;
    }

}
