#pragma once 

#include <inttypes.h>
#include <vector>
#include <array>
#include <tuple>
#include <string>

#include "Vector2D.hpp"
#include "Rotation.hpp"

namespace Model {

    /// An abstract description of a piece. 
    /// The piece is described by a set of vectors which lead to all positions of the piece if an absolute origin is taken into context. 
    /// The Piece struct also provides information about the attach points of the specified piece. 
    /// These are vectors which point from the origin to each poistion where another piece of the same color could be attached.
    struct Piece {
        typedef std::vector<Util::Vector2D> Shape;
        typedef std::array<Util::Vector2D, 2> AttachPoint;
        typedef std::vector<AttachPoint> AttachPoints;
        typedef std::tuple<Shape, AttachPoints> ShapeRotation;

        ///A unique identifier for each shape.
        uint8_t id;

        /// The XML name of the piece.
        const std::string name;

        /// The number of occupied positions.
        const uint8_t size;

        /**
         * A piece can be interpretated in four ratations. If a piece is symmetric two or more rotations will produce equal shapes.
         * To get rid of the extra work of exploring two equal moves this vector contains all rotations which produce different shapes.
         * All rotations not included in the vector would produce equal output to the rotations which are included.
         * 
         * @brief A collection storing all rotations of the piece which lead to an unique shape. 
         */
        std::vector<Rotation> uniqueRotations;

        Piece(Piece* other) = delete;
        Piece(Piece& other) = delete;

        /**
         * Each entry contains information of the shape of the piece and it's attach points in the given rotation.
         * The shape is described by a set of vectors where each vector points to a position of the shape.
         * The attach points are defined by two independent vectors. The first one is a vector pointing from the piece's origin to the attach point.
         * The other one is pointing from the attach point to the nearest position on the shape of the piece.
         * 
         * @brief An array which contains the information to construct the piece in all possible rotations.
         */ 
        std::array<ShapeRotation, 8> rotations;
    };

}