#ifndef CATCH_CONFIG_ENABLE_BENCHMARKING 
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#endif

#include "catch.hpp"
#include "Board.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("Bench Board", "[benchmark][board]") {
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

    BENCHMARK_ADVANCED("Count Drop Positions") (Catch::Benchmark::Chronometer meter) {
        board.dropPiece(piece2);
        board.dropPiece(piece3);
        board.dropPiece(piece1);

        meter.measure([&board] {
            return board.estimateDropPositions(PieceColor::BLUE, PieceColor::YELLOW);
        });

        board.removePiece(piece2);
        board.removePiece(piece3);
        board.removePiece(piece1);
    };

    BENCHMARK_ADVANCED("Analyze Board") (Catch::Benchmark::Chronometer meter) {
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

        meter.measure([&board] {
            return &board.getStatistics();
        });

        for (int i = midGameMoves.size() - 1; i >= 0; --i) {
            board.removePiece(midGameMoves[i]);
        }
    };
}
