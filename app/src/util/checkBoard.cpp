#include <unordered_map>
#include <string>

#include "checkboard.hpp"
#include "color.hpp"

namespace Util {

    BoardPositions checkBoard(const Model::Board& board, const BoardPositions& blue, const BoardPositions& red, const BoardPositions& yellow, const BoardPositions& green) {
        // Vector that contains invalid positions
        BoardPositions invalid;

        const auto makeHash = [](const BoardPosition& pos)-> uint64_t {
            return (static_cast<uint64_t>(pos[0]) << 32) ^ static_cast<uint64_t>(pos[1]);
        };

        //? First compile all colors to avoid expensive looping
        std::unordered_map<uint64_t, Model::PieceColor> expectedColors;

        const auto compilePositions = [&makeHash, &expectedColors, &invalid](const BoardPositions& positions, const Model::PieceColor& color)->void {
            for (const BoardPosition& pos : positions) {
                if (expectedColors.find(makeHash(pos)) != expectedColors.end()) {
                    invalid.push_back(pos);
                } else {
                    expectedColors.insert({makeHash(pos), color});
                }
            }
        };

        compilePositions(blue, Model::PieceColor::BLUE);
        compilePositions(red, Model::PieceColor::RED);
        compilePositions(yellow, Model::PieceColor::YELLOW);
        compilePositions(green, Model::PieceColor::GREEN);

        //? Now do the actual checking
        for (int x = 0; x < 20; x++) {
            for (int y = 0; y < 20; y++) {
                auto search = expectedColors.find(makeHash({x, y}));
                Model::PieceColor expected = search != expectedColors.end() ? search->second : Model::PieceColor::NONE;

                if (board.at(x, y) != expected) {
                    invalid.push_back({x, y});
                }
            }
        }

        return invalid;
    }

}
