#include "catch.hpp"
#include "Board.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("Test Board", "[model]") {
    auto board = Board();
    auto piece1 = DeployedPiece(0, Position(0,0), Rotation::ZERO, PieceColor::BLUE);
    auto piece2 = DeployedPiece(20, Position(10,12), Rotation::PI, PieceColor::YELLOW);
    auto piece3 = DeployedPiece(0, Position(19,0), Rotation::ZERO, PieceColor::BLUE);

    board.dropPiece(piece1);
    board.dropPiece(piece2);
    board.dropPiece(piece3);

    SECTION("Can Drop Pieces") {
        REQUIRE(board.at(0 ,  0) == PieceColor::BLUE);
        REQUIRE(board.at(19,  0) == PieceColor::BLUE);
        REQUIRE(board.at(10, 12) == PieceColor::YELLOW);
        REQUIRE(board.at(10, 11) == PieceColor::YELLOW);
        REQUIRE(board.at(11, 11) == PieceColor::YELLOW);
        REQUIRE(board.at(9 , 11) == PieceColor::YELLOW);
        REQUIRE(board.at(8 , 11) == PieceColor::YELLOW);
    }

    SECTION("Has Valid Drop Positions") {
        auto dropPositionsBlue = board.getDropPositions(PieceColor::BLUE);
        auto dropPositionsYellow = board.getDropPositions(PieceColor::YELLOW);

        REQUIRE_THROWS(board.getDropPositions(PieceColor::NONE));
        REQUIRE(board.canDrop(PieceColor::BLUE, 1, 1));
        REQUIRE_FALSE(board.canDrop(PieceColor::BLUE, 1, 0));
        REQUIRE(board.canDrop(PieceColor::BLUE, 18, 1));

        REQUIRE(board.canDrop(PieceColor::YELLOW, 9, 13));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 11, 13));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 7, 12));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 7, 10));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 12, 12));
        REQUIRE(board.canDrop(PieceColor::YELLOW, 12, 10));

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
        REQUIRE(board.at(10, 11) == PieceColor::NONE);
        REQUIRE(board.at(11, 11) == PieceColor::NONE);
        REQUIRE(board.at(9 , 11) == PieceColor::NONE);
        REQUIRE(board.at(8 , 11) == PieceColor::NONE);
    }

    SECTION("Has Valid Drop Positions After Removing") {
        auto dropPositionsBlue = board.getDropPositions(PieceColor::BLUE);
        auto dropPositionsYellow = board.getDropPositions(PieceColor::YELLOW);

        REQUIRE_FALSE(board.canDrop(PieceColor::BLUE, 1, 1));
        REQUIRE_FALSE(board.canDrop(PieceColor::BLUE, 1, 0));
        REQUIRE_FALSE(board.canDrop(PieceColor::BLUE, 18, 1));

        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 9, 13));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 11, 13));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 7, 12));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 7, 10));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 12, 12));
        REQUIRE_FALSE(board.canDrop(PieceColor::YELLOW, 12, 10));

        REQUIRE(dropPositionsBlue.size() == 0);
        REQUIRE(dropPositionsYellow.size() == 0);
    }
}