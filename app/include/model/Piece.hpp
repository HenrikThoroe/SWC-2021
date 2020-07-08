#pragma once 

#include "Vector2D.hpp"
#include <inttypes.h>
#include <vector>
#include <array>
#include <tuple>

namespace Model {

    /// An abstract description of a piece. 
    /// The piece is described by a set of vectors which lead to all positions of the piece if an absolute origin is taken into context. 
    /// The Piece struct also provides information about the attach points of the specified piece. 
    /// These are vectors which point from the origin to each poistion where another piece of the same color could be attached.s
    struct Piece {
        typedef std::vector<Util::Vector2D> Shape;
        typedef std::array<Util::Vector2D, 2> AttachPoint;
        typedef std::vector<AttachPoint> AttachPoints;
        typedef std::tuple<Shape, AttachPoints> Rotation;

        ///A unique identifier for each shape.
        uint8_t id;

        /**
         * Each entry contains information of the shape of the piece and it's attach points in the given rotation.
         * The shape is described by a set of vectors where each vector points to a position of the shape.
         * The attach points are defined by two independent vectors. The first one is a vector pointing from the piece's origin to the attach point.
         * The other one is pointing from the attach point to the nearest position on the shape of the piece.
         * 
         * @brief An array which contains the information to construct the piece in all possible rotations.
         */ 
        std::array<Rotation, 4> rotations;

        /// A collection of all pieces.
        constexpr static std::array<Piece, 0> allPieces = {

        };
    };

}