#include "StateAnalyzer.hpp"
#include "GameState.hpp"
#include "Board.hpp"

namespace Logic {

    StateAnalyzer::StateAnalyzer(const Model::GameState* gameState) : gameState(gameState) {}

    Util::Rect StateAnalyzer::getBoundingRect(const Model::PieceColor& color) const {
        int maxX = INT_MIN;
        int minX = INT_MAX;
        int maxY = INT_MIN;
        int minY = INT_MAX;

        for (const std::optional<Model::DeployedPiece>& piece : gameState->getMoveHistory()) {
            if (piece.has_value() && piece.value().color == color) {
                for (const Util::Position& pos : piece.value().getOccupiedPositions()) {
                    maxX = std::max(static_cast<int>(pos.x), maxX);
                    maxY = std::max(static_cast<int>(pos.y), maxY);
                    minX = std::min(static_cast<int>(pos.x), minX);
                    minY = std::min(static_cast<int>(pos.y), minY);
                }
            }
        }

        return Util::Rect(minX, maxX, minY, maxY);
    }

    Util::Rect StateAnalyzer::getPlayerArea(const Model::Player& player) const {
        return getBoundingRect(player.getPieceColors()[0]).join(getBoundingRect(player.getPieceColors()[1]));
    }

    Util::Position StateAnalyzer::getPlayerCenter(const Model::Player& player) const {
        int xSum = 0;
        int ySum = 0;
        int vals = 0;

        for (const std::optional<Model::DeployedPiece>& piece : gameState->getMoveHistory()) {
            if (piece.has_value() && (piece.value().color == player.getPieceColors()[0] || piece.value().color == player.getPieceColors()[1])) {
                for (const Util::Position& pos : piece.value().getOccupiedPositions()) {
                    vals += 1;
                    xSum += static_cast<int>(pos.x);
                    ySum += static_cast<int>(pos.y);
                }
            }
        }

        return Util::Position(xSum / vals, ySum / vals);
    }

    int StateAnalyzer::pullFactor(const Model::PieceColor& color, bool swapCorner) const {
        int pull = 0;
        const int startX = gameState->startPositions[static_cast<uint8_t>(color) - 1][0];
        int startY = gameState->startPositions[static_cast<uint8_t>(color) - 1][1];

        if (swapCorner) {
            startY += startY > 0 ? -19 : 19;
        }

        for (const std::optional<Model::DeployedPiece>& piece : gameState->getMoveHistory()) {
            if (piece.has_value() && piece.value().color == color) {
                for (const Util::Position& pos : piece.value().getOccupiedPositions()) {
                    const int x = static_cast<int>(pos.x) - startX;
                    const int y = static_cast<int>(pos.y) - startY;

                    pull = std::max(pull, std::min(abs(x), abs(y)));
                }
            }
        }

        return pull;
    }

    int StateAnalyzer::dropFactor(const std::array<Model::PieceColor, 2>& colors, const std::array<Model::PieceColor, 2>& opponentColors) const {
        const int ownPositions = gameState->getBoard().estimateDropPositions(colors[0], colors[1]);
        const int opponentPositions = gameState->getBoard().estimateDropPositions(opponentColors[0], opponentColors[1]);

        return ownPositions - 2 * opponentPositions;
    }

    int StateAnalyzer::pushFactor(const Model::PieceColor& color) const {
        int push = 0;
        const int startX = gameState->startPositions[static_cast<uint8_t>(color) - 1][0];
        int startY = gameState->startPositions[static_cast<uint8_t>(color) - 1][1];

        for (const std::optional<Model::DeployedPiece>& piece : gameState->getMoveHistory()) {
            if (piece.has_value() && piece.value().color == color) {
                for (const Util::Position& pos : piece.value().getOccupiedPositions()) {
                    const int x = static_cast<int>(pos.x) - startX;
                    const int y = static_cast<int>(pos.y) - startY;

                    push += std::max(abs(x), abs(y));
                }
            }
        }

        return push;
    }

    int StateAnalyzer::strategyPoints(const std::array<Model::PieceColor, 2>& colors, const std::array<Model::PieceColor, 2>& opponentColors) const {
        //? Prepare information
        const Model::Board& board = gameState->getBoard();

        const std::array<int, 4> normalizedStart = { 
            gameState->startPositions[0][0] + 20 * gameState->startPositions[0][1],
            gameState->startPositions[1][0] + 20 * gameState->startPositions[1][1],
            gameState->startPositions[2][0] + 20 * gameState->startPositions[2][1],
            gameState->startPositions[3][0] + 20 * gameState->startPositions[3][1]
        };
        bool horizontal =
            static_cast<int>(board.at(0, 0)) >= 3                       // If top left is team two
            ? ( static_cast<int>(board.at(0, 19)) >= 3 ? true : false)  // YES: If bottom left is team two -> horizontal
            : ( static_cast<int>(board.at(0, 19)) >= 3 ? false : true); // NO: If bottom left is team two -> vertical

        const std::array<Model::BoardStatistics, 4>& stats = board.getStatistics(horizontal);
        const std::array<int, 2> colorIdx = { static_cast<int>(colors[0]) - 1, static_cast<int>(colors[1]) - 1 };
        const std::array<int, 2> opponentColorIdx = { static_cast<int>(opponentColors[0]) - 1, static_cast<int>(opponentColors[1]) - 1 };
        const std::array<Util::Rect, 4> bounds = {
            getBoundingRect(static_cast<Model::PieceColor>(1)),
            getBoundingRect(static_cast<Model::PieceColor>(2)),
            getBoundingRect(static_cast<Model::PieceColor>(3)),
            getBoundingRect(static_cast<Model::PieceColor>(4))
        };
        std::array<int, 4> startIndex {};
        std::array<int, 4> opposingNeighbour{};
        std::array<int, 4> oppositeCorner{};
        std::array<int, 4> startSide{};


        for (int i = 0; i < 4; ++i) {
            switch (normalizedStart[i]) {
                case 0:
                    // Top left
                    startIndex[i] = 0;
                    opposingNeighbour[i] = horizontal ? 1 : 3;
                    oppositeCorner[i] = 2;
                    startSide[i] = 0;
                    break;
                case 19:
                    // Top right
                    startIndex[i] = 1;
                    opposingNeighbour[i] = horizontal ? 0 : 2;
                    oppositeCorner[i] = 3;
                    startSide[i] = horizontal ? 1 : 0;
                    break;
                case 399:
                    // Bottom right
                    startIndex[i] = 2;
                    opposingNeighbour[i] = horizontal ? 3 : 1;
                    oppositeCorner[i] = 0;
                    startSide[i] = 1;
                    break;
                case 380:
                    // Bottom left
                    startIndex[i] = 3;
                    opposingNeighbour[i] = horizontal ? 2 :0;
                    oppositeCorner[i] = 1;
                    startSide[i] = horizontal ? 0 : 1;
                    break;
            }
        }

        //* Start 

        if (gameState->getTurn() < 16) {
            //? Push each color to the middle 

            return stats[colorIdx[0]].pullFactor[oppositeCorner[colorIdx[0]]] + stats[colorIdx[1]].pullFactor[oppositeCorner[colorIdx[1]]];
        }

        //* Mid

        if (gameState->getTurn() < 50) {
            int drop = 0;
            int size = 0;
            int block = 0;
            int dir = 0;

            dir += stats[colorIdx[0]].pullFactor[opposingNeighbour[colorIdx[0]]];
            dir += stats[colorIdx[1]].pullFactor[opposingNeighbour[colorIdx[1]]];

            dir -= stats[opponentColorIdx[0]].pullFactor[opposingNeighbour[opponentColorIdx[0]]] * 2;
            dir -= stats[opponentColorIdx[1]].pullFactor[opposingNeighbour[opponentColorIdx[1]]] * 2;

            size -= bounds[opponentColorIdx[0]].size();
            size -= bounds[opponentColorIdx[1]].size();

            drop += stats[colorIdx[0]].dropPositions;
            drop += stats[colorIdx[1]].dropPositions;

            block += stats[opponentColorIdx[0]].opponentBlockedCorners * 100;
            block += stats[opponentColorIdx[1]].opponentBlockedCorners * 100;

            for (int i = 0; i < 8; ++i) {
                drop -= stats[opponentColorIdx[0]].ratedDropPositions[i] * i * 4;
                drop -= stats[opponentColorIdx[1]].ratedDropPositions[i] * i * 4;
            }

            return drop + size + block + dir;
        }

        //* Late

        int drop = 0;
        int size = 0;
        int block = 0;
        int dir = 0;

        //? Penalty when the team is blocking itself

        block -= stats[colorIdx[0]].friendlyBlockedCorners;
        block -= stats[colorIdx[1]].friendlyBlockedCorners;

        //? Block the colors of the opponent

        block += stats[opponentColorIdx[0]].opponentBlockedCorners * 4;
        block += stats[opponentColorIdx[1]].opponentBlockedCorners * 4;

        //? Maximize own drop positions while minimizing opponent drop positions

        for (int i = 0; i < 8; ++i) {
            drop += stats[colorIdx[0]].ratedDropPositions[i] * i;
            drop += stats[colorIdx[1]].ratedDropPositions[i] * i;

            drop -= stats[opponentColorIdx[0]].ratedDropPositions[i] * i;
            drop -= stats[opponentColorIdx[1]].ratedDropPositions[i] * i;
        }

        //? Push own color to the opposite side and prevent the same from the opponent

        dir -= stats[opponentColorIdx[0]].alignment[startSide[opponentColorIdx[0]]];
        dir -= stats[opponentColorIdx[1]].alignment[startSide[opponentColorIdx[1]]];

        dir += stats[colorIdx[0]].alignment[startSide[colorIdx[0]]];
        dir += stats[colorIdx[1]].alignment[startSide[colorIdx[1]]];

        return drop + size + block + dir;
    }

}
