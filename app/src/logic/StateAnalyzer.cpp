#include "StateAnalyzer.hpp"
#include "GameState.hpp"

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
        return gameState->getBoard().estimateDropPositions(colors[0], colors[1]) - gameState->getBoard().estimateDropPositions(opponentColors[0], opponentColors[1]);
    }

    int StateAnalyzer::strategyPoints(const std::array<Model::PieceColor, 2>& colors, const std::array<Model::PieceColor, 2>& opponentColors) const {
        //* Early Game
        // Pull both colors to the opposite corners to build a triangle

        if (gameState->getTurn() < 20) {
            return pullFactor(colors[0]) * pullFactor(colors[1]) + (pullFactor(colors[0], true) * pullFactor(colors[1], true) / 4);
        } 

        //* Mid Game
        // Pull each color to the opposite corner with the same y value and optimize drop positions
        // This will build two more triangles

        const Util::Rect c1Rect = getBoundingRect(colors[0]);
        const Util::Rect c2Rect = getBoundingRect(colors[0]);
        const int sizeFactor = c1Rect.size() * c2Rect.size();

        if (gameState->getTurn() < 40) {
            return pullFactor(colors[0], true) * pullFactor(colors[1], true) + dropFactor(colors, opponentColors) + (pullFactor(colors[0]) * pullFactor(colors[1]) / 4) + sizeFactor;
        }

        //* Late Game
        // Use created space by deploying everywhere and optimize drop positions with an higher influence

        return dropFactor(colors, opponentColors) * 10 + pullFactor(colors[0]) + pullFactor(colors[1]) + sizeFactor;
    }

}
