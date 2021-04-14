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

    int StateAnalyzer::basicStrategie(const std::array<Model::BoardStatistics, 4>& stats, const std::array<int, 2> colorIdx, const std::array<int, 2> opponentColorIdx) const {
        int spread = 0;
        int drop = 0;
        int block = 0;

        //* Drop 

        drop += stats[colorIdx[0]].dropPositions * 8;
        drop += stats[colorIdx[1]].dropPositions * 8;

        drop -= stats[opponentColorIdx[0]].dropPositions * 8;
        drop -= stats[opponentColorIdx[1]].dropPositions * 8;

        for (int i = 0; i < 8; ++i) {
            drop += stats[colorIdx[0]].ratedDropPositions[i] * i;
            drop += stats[colorIdx[1]].ratedDropPositions[i] * i;

            drop -= stats[opponentColorIdx[0]].ratedDropPositions[i] * i;
            drop -= stats[opponentColorIdx[1]].ratedDropPositions[i] * i;
        }

        //* Block

        //? Penalty when the team is blocking itself

        block -= stats[colorIdx[0]].friendlyBlockedCorners * 4;
        block -= stats[colorIdx[1]].friendlyBlockedCorners * 4;

        //? Block the colors of the opponent

        block += stats[opponentColorIdx[0]].opponentBlockedCorners;
        block += stats[opponentColorIdx[1]].opponentBlockedCorners;

        //* Spread 

        spread += stats[colorIdx[0]].teamPushFactor + stats[colorIdx[1]].teamPushFactor;
        spread -= stats[opponentColorIdx[0]].pushFactor + stats[opponentColorIdx[1]].pushFactor;

        return spread + block + drop;
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
            ? (static_cast<int>(board.at(0, 19)) >= 3 ? true : false)   // YES: If bottom left is team two -> horizontal
            : (static_cast<int>(board.at(0, 19)) >= 3 ? false : true);  // NO: If bottom left is team two -> vertical

        const std::array<Model::BoardStatistics, 4>& stats = board.getStatistics(horizontal);
        const std::array<int, 2> colorIdx = { static_cast<int>(colors[0]) - 1, static_cast<int>(colors[1]) - 1 };
        const std::array<int, 2> opponentColorIdx = { static_cast<int>(opponentColors[0]) - 1, static_cast<int>(opponentColors[1]) - 1 };

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

        if (gameState->getTurn() < 20) {
            //? Push each color to the middle 

            return stats[colorIdx[0]].pullFactor[oppositeCorner[colorIdx[0]]] + stats[colorIdx[1]].pullFactor[oppositeCorner[colorIdx[1]]];
        }

        return basicStrategie(stats, colorIdx, opponentColorIdx);
    }

}
