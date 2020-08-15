#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "DeployedPiece.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("Bench Deployed Piece", "[benchmark]") {
    auto piece1 = DeployedPiece(0, Position(0,0), Rotation::ZERO, PieceColor::BLUE);
    auto piece2 = DeployedPiece(20, Position(10,12), Rotation::PI, PieceColor::YELLOW);
    auto piece3 = DeployedPiece(0, Position(19,0), Rotation::ZERO, PieceColor::BLUE);

    BENCHMARK_ADVANCED("Prepare Occupied Fields") (Catch::Benchmark::Chronometer meter) {
        auto piece = DeployedPiece(20, Position(10,12), Rotation::PI, PieceColor::YELLOW, false);
        meter.measure([&piece] {
            piece.prepareOccupiedFields();
        });

        return piece.getOccupiedPositions();
    };

    BENCHMARK_ADVANCED("Prepare Attach Fields") (Catch::Benchmark::Chronometer meter) {
        auto piece = DeployedPiece(20, Position(10,12), Rotation::PI, PieceColor::YELLOW, false);
        meter.measure([&piece] {
            piece.prepareAttachPoints();
        });

        return piece.getAttachPoints();
    };
}