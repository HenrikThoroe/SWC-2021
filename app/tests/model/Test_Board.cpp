#include "catch.hpp"
#include "Board.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("Test Board", "[model]") {
    auto board = Board();
    auto piece1 = DeployedPiece(0, Position(0,0), Rotation::ZERO, PieceColor::BLUE);
    auto piece2 = DeployedPiece(20, Position(10,12), Rotation::PI, PieceColor::YELLOW);
    auto piece3 = DeployedPiece(0, Position(19,0), Rotation::ZERO, PieceColor::BLUE);

    SECTION("Can Drop Pieces") {
        board.dropPiece(piece1);
        board.dropPiece(piece2);
        board.dropPiece(piece3);

        REQUIRE(board.at(0 ,  0) == PieceColor::BLUE);
        REQUIRE(board.at(10, 12) == PieceColor::YELLOW);
        REQUIRE(board.at(10, 11) == PieceColor::YELLOW);
        REQUIRE(board.at(11, 11) == PieceColor::YELLOW);
        REQUIRE(board.at(9 , 11) == PieceColor::YELLOW);
        REQUIRE(board.at(8 , 11) == PieceColor::YELLOW);
    }
}