#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "Board.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("Bench Board", "[benchmark]") {
    auto board = Board();
    auto piece1 = DeployedPiece(0, Position(0,0), Rotation::ZERO, PieceColor::BLUE);
    auto piece2 = DeployedPiece(20, Position(10,12), Rotation::PI, PieceColor::YELLOW);
    auto piece3 = DeployedPiece(0, Position(19,0), Rotation::ZERO, PieceColor::BLUE);

    BENCHMARK_ADVANCED("Drop Piece") (Catch::Benchmark::Chronometer meter) {
        meter.measure([&board, &piece2] {
            board.dropPiece(piece2);
        });

        board.removePiece(piece2);
    };

    BENCHMARK_ADVANCED("Remove Piece") (Catch::Benchmark::Chronometer meter) {
        board.dropPiece(piece2);

        meter.measure([&board, &piece2] {
            board.removePiece(piece2);
        });
    };

    BENCHMARK_ADVANCED("Get Drop Positions") (Catch::Benchmark::Chronometer meter) {
        board.dropPiece(piece2);
        board.dropPiece(piece3);
        board.dropPiece(piece1);

        meter.measure([&board] {
            return board.getDropPositions(PieceColor::BLUE);
        });

        board.removePiece(piece2);
        board.removePiece(piece3);
        board.removePiece(piece1);
    };
}
