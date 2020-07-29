#include "catch.hpp"
#include "DeployedPiece.hpp"
#include "PieceCollection.hpp"
#include "Position.hpp"

using namespace Model;
using namespace Util;

TEST_CASE("DeployedPiece Test", "[model]") {
    // 1x1 at top left corner
    auto simple = DeployedPiece(0, Position(0, 0), Rotation::ZERO, PieceColor::RED);

    //      +
    //    + + + +
    auto complex = DeployedPiece(20, Position(0, 0), Rotation::ZERO, PieceColor::RED);

    SECTION("Basic") {
        auto occupied = simple.getOccupiedPositions();
        auto attachPoints = simple.getAttachPoints();
        auto validation = simple.getValidationPoints();

        REQUIRE(occupied.size() == 1);
        REQUIRE(attachPoints.size() == 4);

        REQUIRE(occupied[0] == Position(0, 0));

        REQUIRE(attachPoints[0] == Position(-1, -1));
        REQUIRE(attachPoints[1] == Position(1, -1));
        REQUIRE(attachPoints[2] == Position(-1, 1));
        REQUIRE(attachPoints[3] == Position(1, 1));

        REQUIRE(validation[0] == Position(-2, -2));
        REQUIRE(validation[1] == Position(2, -2));
        REQUIRE(validation[2] == Position(-2, 2));
        REQUIRE(validation[3] == Position(2, 2));
    }

    SECTION("Complex") {
        auto occupied = complex.getOccupiedPositions();
        auto attachPoints = complex.getAttachPoints();
        auto validation = complex.getValidationPoints();

        std::array<Position, 6> expectedAttachPoints = {
            Position(-1, -1),
            Position(1, -1),
            Position(-2, 0),
            Position(-2, 2),
            Position(3, 0),
            Position(3, 2)
        };

        std::array<Position, 6> expectedValidationPoints = {
            Position(-2, -2),
            Position(2, -2),
            Position(-3, -1),
            Position(-3, 3),
            Position(4, -1),
            Position(4, 3)
        };

        REQUIRE(occupied.size() == 5);
        REQUIRE(attachPoints.size() == 6);
        REQUIRE(validation.size() == 6);

        for (auto& expected : expectedAttachPoints) {
            bool included = false;
            for (auto& point : attachPoints) {
                if (point == expected) {
                    if (included) {
                        FAIL("Already Included");
                    }
                    included = true;
                }
            }

            INFO(expected);
            REQUIRE(included);
        }
    }

    SECTION("Can Rotate") {
        std::array<DeployedPiece, 4> rotations = {
            DeployedPiece(20, Position(0,0), Rotation::ZERO, PieceColor::RED),
            DeployedPiece(20, Position(0,0), Rotation::ONEHALFPI, PieceColor::RED),
            DeployedPiece(20, Position(0,0), Rotation::PI, PieceColor::RED),
            DeployedPiece(20, Position(0,0), Rotation::THREEHALFPI, PieceColor::RED)
        };

        REQUIRE(rotations[0].getOccupiedPositions()[0] == Position(0, 0));
        REQUIRE(rotations[0].getOccupiedPositions()[1] == Position(0, 1));
        REQUIRE(rotations[0].getOccupiedPositions()[2] == Position(-1, 1));
        REQUIRE(rotations[0].getOccupiedPositions()[3] == Position(1, 1));
        REQUIRE(rotations[0].getOccupiedPositions()[4] == Position(2, 1));

        REQUIRE(rotations[1].getOccupiedPositions()[0] == Position(0, 0));
        REQUIRE(rotations[1].getOccupiedPositions()[1] == Position(-1, 0));
        REQUIRE(rotations[1].getOccupiedPositions()[2] == Position(-1, -1));
        REQUIRE(rotations[1].getOccupiedPositions()[3] == Position(-1, 1));
        REQUIRE(rotations[1].getOccupiedPositions()[4] == Position(-1, 2));

        REQUIRE(rotations[2].getOccupiedPositions()[0] == Position(0, 0));
        REQUIRE(rotations[2].getOccupiedPositions()[1] == Position(0, -1));
        REQUIRE(rotations[2].getOccupiedPositions()[2] == Position(1, -1));
        REQUIRE(rotations[2].getOccupiedPositions()[3] == Position(-1, -1));
        REQUIRE(rotations[2].getOccupiedPositions()[4] == Position(-2, -1));

        REQUIRE(rotations[3].getOccupiedPositions()[0] == Position(0, 0));
        REQUIRE(rotations[3].getOccupiedPositions()[1] == Position(1, 0));
        REQUIRE(rotations[3].getOccupiedPositions()[2] == Position(1, 1));
        REQUIRE(rotations[3].getOccupiedPositions()[3] == Position(1, -1));
        REQUIRE(rotations[3].getOccupiedPositions()[4] == Position(1, -2));
    }
}