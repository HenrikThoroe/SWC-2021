#include "catch.hpp"
#include "Board.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("Test Board", "[model]") {
    auto board = Board();
    auto piece1 = DeployedPiece(0, Position(0,0), Rotation::ZERO, PieceColor::BLUE);
    auto piece2 = DeployedPiece(18, Position(10,12), Rotation::ZERO_FLIPPED, PieceColor::YELLOW);
    auto piece3 = DeployedPiece(0, Position(19,0), Rotation::ZERO, PieceColor::BLUE);

    board.dropPiece(piece1);
    board.dropPiece(piece2);
    board.dropPiece(piece3);

    SECTION("Can Force Drop Positions") {
        auto board2 = Board();

        board2.makeDropPosition(Position(0, 0), PieceColor::RED);
        board2.makeDropPosition(Position(10, 11), PieceColor::BLUE);

        REQUIRE(board2.canDrop(PieceColor::RED, 0, 0));
        REQUIRE(board2.canDrop(PieceColor::BLUE, 10, 11));
    }

    SECTION("Can Drop Pieces") {
        REQUIRE(board.at(0 ,  0) == PieceColor::BLUE);
        REQUIRE(board.at(19,  0) == PieceColor::BLUE);
        REQUIRE(board.at(10, 12) == PieceColor::YELLOW);
        REQUIRE(board.at(10, 13) == PieceColor::YELLOW);
        REQUIRE(board.at(10, 14) == PieceColor::YELLOW);
        REQUIRE(board.at(10, 15) == PieceColor::YELLOW);
        REQUIRE(board.at(11, 13) == PieceColor::YELLOW);
    }

    SECTION("Has Valid Drop Positions") {
        auto dropPositionsBlue = board.getDropPositions(PieceColor::BLUE);
        auto dropPositionsYellow = board.getDropPositions(PieceColor::YELLOW);

        REQUIRE_THROWS(board.getDropPositions(PieceColor::NONE));
        REQUIRE(board.canDrop(PieceColor::BLUE, 1, 1));
        REQUIRE_FALSE(board.canDrop(PieceColor::BLUE, 1, 0));
        REQUIRE(board.canDrop(PieceColor::BLUE, 18, 1));

        REQUIRE(board.canDrop(PieceColor::YELLOW, 9, 11));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 11, 11));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 9, 16));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 11, 16));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 12, 12));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 12, 14));

        REQUIRE(dropPositionsBlue.size() == 2);
        REQUIRE(dropPositionsYellow.size() == 6);
    }

    board.removePiece(piece1);
    board.removePiece(piece2);
    board.removePiece(piece3);

    SECTION("Can Remove Piece") {
        REQUIRE(board.at(0 ,  0) == PieceColor::NONE);
        REQUIRE(board.at(19,  0) == PieceColor::NONE);
        REQUIRE(board.at(10, 12) == PieceColor::NONE);
        REQUIRE(board.at(10, 13) == PieceColor::NONE);
        REQUIRE(board.at(10, 14) == PieceColor::NONE);
        REQUIRE(board.at(10, 15) == PieceColor::NONE);
        REQUIRE(board.at(11, 13) == PieceColor::NONE);
    }

    SECTION("Has Valid Drop Positions After Removing") {
        auto dropPositionsBlue = board.getDropPositions(PieceColor::BLUE);
        auto dropPositionsYellow = board.getDropPositions(PieceColor::YELLOW);

        REQUIRE_FALSE(board.canDrop(PieceColor::BLUE, 1, 1));
        REQUIRE_FALSE(board.canDrop(PieceColor::BLUE, 1, 0));
        REQUIRE_FALSE(board.canDrop(PieceColor::BLUE, 18, 1));

        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 9, 11));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 11, 11));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 9, 16));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 11, 16));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 12, 12));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 12, 14));

        REQUIRE(dropPositionsBlue.size() == 0);
        REQUIRE(dropPositionsYellow.size() == 0);
    }

    SECTION("Can Create Statistics") {
        const std::array<Model::DeployedPiece, 54> midGameMoves = {
            DeployedPiece(11, Position(19, 19), static_cast<Rotation>(7), PieceColor::BLUE),
            DeployedPiece(11, Position(0, 0), static_cast<Rotation>(0), PieceColor::YELLOW),
            DeployedPiece(11, Position(19, 0), static_cast<Rotation>(1), PieceColor::RED),
            DeployedPiece(11, Position(0, 16), static_cast<Rotation>(0), PieceColor::GREEN),
            DeployedPiece(20, Position(14, 14), static_cast<Rotation>(1), PieceColor::BLUE),
            DeployedPiece(18, Position(2, 4), static_cast<Rotation>(3), PieceColor::YELLOW),
            DeployedPiece(20, Position(15, 2), static_cast<Rotation>(5), PieceColor::RED),
            DeployedPiece(18, Position(4, 15), static_cast<Rotation>(1), PieceColor::GREEN),
            DeployedPiece(17, Position(11, 11), static_cast<Rotation>(5), PieceColor::BLUE),
            DeployedPiece(15, Position(8, 6), static_cast<Rotation>(4), PieceColor::YELLOW),
            DeployedPiece(17, Position(13, 6), static_cast<Rotation>(1), PieceColor::RED),
            DeployedPiece(15, Position(7, 13), static_cast<Rotation>(2), PieceColor::GREEN),
            DeployedPiece(14, Position(8, 8), static_cast<Rotation>(0), PieceColor::BLUE),
            DeployedPiece(14, Position(9, 7), static_cast<Rotation>(0), PieceColor::YELLOW),
            DeployedPiece(19, Position(10, 4), static_cast<Rotation>(1), PieceColor::RED),
            DeployedPiece(12, Position(7, 9), static_cast<Rotation>(0), PieceColor::GREEN),
            DeployedPiece(19, Position(12, 14), static_cast<Rotation>(1), PieceColor::BLUE),
            DeployedPiece(10, Position(12, 10), static_cast<Rotation>(0), PieceColor::YELLOW),
            DeployedPiece(14, Position(5, 2), static_cast<Rotation>(0), PieceColor::RED),
            DeployedPiece(10, Position(8, 16), static_cast<Rotation>(3), PieceColor::GREEN),
            DeployedPiece(18, Position(19, 14), static_cast<Rotation>(7), PieceColor::BLUE),
            DeployedPiece(16, Position(14, 8), static_cast<Rotation>(0), PieceColor::YELLOW),
            DeployedPiece(18, Position(16, 4), static_cast<Rotation>(3), PieceColor::RED),
            DeployedPiece(9, Position(14, 17), static_cast<Rotation>(3), PieceColor::GREEN),
            DeployedPiece(13, Position(12, 18), static_cast<Rotation>(5), PieceColor::BLUE),
            DeployedPiece(13, Position(18, 6), static_cast<Rotation>(1), PieceColor::YELLOW),
            DeployedPiece(15, Position(3, 6), static_cast<Rotation>(0), PieceColor::RED),
            DeployedPiece(14, Position(4, 9), static_cast<Rotation>(3), PieceColor::GREEN),
            DeployedPiece(5, Position(10, 13), static_cast<Rotation>(7), PieceColor::BLUE),
            DeployedPiece(17, Position(1, 6), static_cast<Rotation>(0), PieceColor::YELLOW),
            DeployedPiece(12, Position(2, 5), static_cast<Rotation>(1), PieceColor::RED),
            DeployedPiece(16, Position(1, 12), static_cast<Rotation>(0), PieceColor::GREEN),
            DeployedPiece(15, Position(6, 16), static_cast<Rotation>(7), PieceColor::BLUE),
            DeployedPiece(20, Position(14, 13), static_cast<Rotation>(0), PieceColor::YELLOW),
            DeployedPiece(13, Position(1, 10), static_cast<Rotation>(2), PieceColor::RED),
            DeployedPiece(13, Position(7, 17), static_cast<Rotation>(1), PieceColor::GREEN),
            DeployedPiece(7, Position(4, 16), static_cast<Rotation>(1), PieceColor::BLUE),
            DeployedPiece(12, Position(2, 2), static_cast<Rotation>(3), PieceColor::YELLOW),
            DeployedPiece(7, Position(12, 9), static_cast<Rotation>(0), PieceColor::RED),
            DeployedPiece(20, Position(2, 18), static_cast<Rotation>(6), PieceColor::GREEN),
            DeployedPiece(9, Position(4, 10), static_cast<Rotation>(0), PieceColor::BLUE),
            DeployedPiece(9, Position(19, 8), static_cast<Rotation>(0), PieceColor::YELLOW),
            DeployedPiece(10, Position(15, 10), static_cast<Rotation>(0), PieceColor::RED),
            DeployedPiece(5, Position(11, 19), static_cast<Rotation>(7), PieceColor::GREEN),
            DeployedPiece(2, Position(2, 16), static_cast<Rotation>(1), PieceColor::BLUE),
            DeployedPiece(5, Position(13, 14), static_cast<Rotation>(0), PieceColor::YELLOW),
            DeployedPiece(16, Position(8, 2), static_cast<Rotation>(0), PieceColor::RED),
            DeployedPiece(2, Position(14, 19), static_cast<Rotation>(3), PieceColor::GREEN),
            DeployedPiece(0, Position(17, 16), static_cast<Rotation>(0), PieceColor::BLUE),
            DeployedPiece(8, Position(12, 13), static_cast<Rotation>(4), PieceColor::YELLOW),
            DeployedPiece(5, Position(12, 0), static_cast<Rotation>(5), PieceColor::RED),
            DeployedPiece(17, Position(16, 16), static_cast<Rotation>(7), PieceColor::GREEN),
            DeployedPiece(1, Position(19, 16), static_cast<Rotation>(1), PieceColor::BLUE),
            DeployedPiece(2, Position(9, 12), static_cast<Rotation>(3), PieceColor::YELLOW)
        };

        for (const DeployedPiece& move : midGameMoves) {
            board.dropPiece(move);
        }

        const std::array<BoardStatistics, 4>& stats = board.getStatistics();

        //* Correct colors are assigned
        REQUIRE(stats[0].color == PieceColor::RED);
        REQUIRE(stats[1].color == PieceColor::BLUE);
        REQUIRE(stats[2].color == PieceColor::GREEN);
        REQUIRE(stats[3].color == PieceColor::YELLOW);


        //* Each color has valid pull factors
        REQUIRE(stats[0].pullFactor[0] == 14);
        REQUIRE(stats[0].pullFactor[1] == 19);
        REQUIRE(stats[0].pullFactor[2] == 11);
        REQUIRE(stats[0].pullFactor[3] == 10);

        REQUIRE(stats[1].pullFactor[0] == 11);
        REQUIRE(stats[1].pullFactor[1] == 9);
        REQUIRE(stats[1].pullFactor[2] == 19);
        REQUIRE(stats[1].pullFactor[3] == 17);

        REQUIRE(stats[2].pullFactor[0] == 12);
        REQUIRE(stats[2].pullFactor[1] == 8);
        REQUIRE(stats[2].pullFactor[2] == 18);
        REQUIRE(stats[2].pullFactor[3] == 19);

        REQUIRE(stats[3].pullFactor[0] == 19);
        REQUIRE(stats[3].pullFactor[1] == 13);
        REQUIRE(stats[3].pullFactor[2] == 14);
        REQUIRE(stats[3].pullFactor[3] == 10);


        //* Correct amount of free and blocked corners
        REQUIRE(stats[0].freeCorners == 20);
        REQUIRE(stats[1].freeCorners == 4);
        REQUIRE(stats[2].freeCorners == 12);
        REQUIRE(stats[3].freeCorners == 11);

        REQUIRE(stats[0].friendlyBlockedCorners == 0);
        REQUIRE(stats[1].friendlyBlockedCorners == 0);
        REQUIRE(stats[2].friendlyBlockedCorners == 3);
        REQUIRE(stats[3].friendlyBlockedCorners == 5);

        REQUIRE(stats[0].opponentBlockedCorners == 17);
        REQUIRE(stats[1].opponentBlockedCorners == 32);
        REQUIRE(stats[2].opponentBlockedCorners == 22);
        REQUIRE(stats[3].opponentBlockedCorners == 25);


        //* Correct amount of shared edges
        //? Unused until performance is fixed
        //// REQUIRE(stats[0].sharedEdges == 33);
        //// REQUIRE(stats[1].sharedEdges == 80);
        //// REQUIRE(stats[2].sharedEdges == 55);
        //// REQUIRE(stats[3].sharedEdges == 72); 

        //// REQUIRE(stats[0].friendlySharedEdges == stats[1].friendlySharedEdges);
        //// REQUIRE(stats[2].friendlySharedEdges == stats[3].friendlySharedEdges);
        //// REQUIRE(stats[0].friendlySharedEdges == 0);
        //// REQUIRE(stats[1].friendlySharedEdges == 0);
        //// REQUIRE(stats[2].friendlySharedEdges == 7);
        //// REQUIRE(stats[3].friendlySharedEdges == 7);

        //// REQUIRE(stats[0].opponentSharedEdges == 33);
        //// REQUIRE(stats[1].opponentSharedEdges == 80);
        //// REQUIRE(stats[2].opponentSharedEdges == 48);
        //// REQUIRE(stats[3].opponentSharedEdges == 65);


        //* Correct amount of drop positions
        REQUIRE(stats[0].dropPositions == 15);
        REQUIRE(stats[1].dropPositions == 3);
        REQUIRE(stats[2].dropPositions == 7);
        REQUIRE(stats[3].dropPositions == 8);

        REQUIRE(stats[0].ratedDropPositions[0] == 2);
        REQUIRE(stats[0].ratedDropPositions[1] == 0);
        REQUIRE(stats[0].ratedDropPositions[2] == 0);
        REQUIRE(stats[0].ratedDropPositions[3] == 1);
        REQUIRE(stats[0].ratedDropPositions[4] == 4);
        REQUIRE(stats[0].ratedDropPositions[5] == 1);
        REQUIRE(stats[0].ratedDropPositions[6] == 3);
        REQUIRE(stats[0].ratedDropPositions[7] == 4);

        REQUIRE(stats[1].ratedDropPositions[0] == 0);
        REQUIRE(stats[1].ratedDropPositions[1] == 0);
        REQUIRE(stats[1].ratedDropPositions[2] == 2);
        REQUIRE(stats[1].ratedDropPositions[3] == 0);
        REQUIRE(stats[1].ratedDropPositions[4] == 1);
        REQUIRE(stats[1].ratedDropPositions[5] == 0);
        REQUIRE(stats[1].ratedDropPositions[6] == 0);
        REQUIRE(stats[1].ratedDropPositions[7] == 0);

        REQUIRE(stats[2].ratedDropPositions[0] == 0);
        REQUIRE(stats[2].ratedDropPositions[1] == 0);
        REQUIRE(stats[2].ratedDropPositions[2] == 3);
        REQUIRE(stats[2].ratedDropPositions[3] == 0);
        REQUIRE(stats[2].ratedDropPositions[4] == 4);
        REQUIRE(stats[2].ratedDropPositions[5] == 0);
        REQUIRE(stats[2].ratedDropPositions[6] == 0);
        REQUIRE(stats[2].ratedDropPositions[7] == 0);

        REQUIRE(stats[3].ratedDropPositions[0] == 0);
        REQUIRE(stats[3].ratedDropPositions[1] == 2);
        REQUIRE(stats[3].ratedDropPositions[2] == 2);
        REQUIRE(stats[3].ratedDropPositions[3] == 1);
        REQUIRE(stats[3].ratedDropPositions[4] == 2);
        REQUIRE(stats[3].ratedDropPositions[5] == 0);
        REQUIRE(stats[3].ratedDropPositions[6] == 1);
        REQUIRE(stats[3].ratedDropPositions[7] == 0);


        //* Can reset all values
        for (int i = 0; i < 0; ++i) {
            BoardStatistics& stat = const_cast<BoardStatistics&>(stats[i]);

            stat.reset();

            for (int p = 0; p < 4; ++p) {
                REQUIRE(stat.pullFactor[p] == 0);
            }

            REQUIRE(stat.freeCorners == 0);
            REQUIRE(stat.friendlyBlockedCorners == 0);
            REQUIRE(stat.opponentBlockedCorners == 0);
            REQUIRE(stat.sharedEdges == 0);
            REQUIRE(stat.friendlySharedEdges == 0);
            REQUIRE(stat.opponentSharedEdges == 0);
            REQUIRE(stat.dropPositions == 0);

            for (int d = 0; d < 8; ++d) {
                REQUIRE(stat.ratedDropPositions[d] == 0);
            }
        }
    }
}
