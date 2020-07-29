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

    WARN(board);

    REQUIRE(board.fields[0][0] == uint8_t(PieceColor::BLUE));
    REQUIRE(board.fields[12][10] == uint8_t(PieceColor::YELLOW));
    REQUIRE(board.fields[9][12] == uint8_t(PieceColor::YELLOW));
    REQUIRE(board.fields[9][13] == uint8_t(PieceColor::YELLOW));
    REQUIRE(board.fields[9][11] == uint8_t(PieceColor::YELLOW));
    REQUIRE(board.fields[9][10] == uint8_t(PieceColor::YELLOW));
}