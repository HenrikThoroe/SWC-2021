#pragma once

namespace Util {

    /// The mathematical representation of a two dimensional vector (not C++ array like vector).
    class Vector2D {
        public:
            /// @brief The x offset.
            int x;

            /// @brief The y offset.
            int y;

            Vector2D(int x, int y);
            Vector2D(const Vector2D* other);
            Vector2D(const Vector2D& other);

            /// Scales the vector instance by the given factor.
            void scale(const int& factor);

            /// Shifts the vector with the passed vector. Equal to addtion of the x and y value of both vectors.
            void shift(const Vector2D& offset);

            /// The length of the vector.
            int length() const;

            /// Similiar to scale(const int&) but does not mutate the instance.
            Vector2D scaled(const int& factor) const;

            /// Similiar to shift(const Vector2D&) but does not mutate the instance.
            Vector2D shifted(const Vector2D& offset) const;

            Vector2D operator + (const Vector2D& offset) const;

            Vector2D operator * (const int& factor) const;
    };

}