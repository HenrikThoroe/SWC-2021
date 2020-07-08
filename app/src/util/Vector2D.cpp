#include "Vector2D.hpp"
#include <math.h>

namespace Util {

    Vector2D::Vector2D(int x, int y) : x(x), y(y) {};

    Vector2D::Vector2D(const Vector2D& other) : x(other.x), y(other.y) {};

    Vector2D::Vector2D(const Vector2D* other) : x(other->x), y(other->y) {};

    void Vector2D::scale(const int& factor) {
        x = factor * x;
        y = factor * y;
    }

    void Vector2D::shift(const Vector2D& other) {
        x = x + other.x;
        y = y + other.y;
    }

    Vector2D Vector2D::scaled(const int& factor) const {
        Vector2D scaled = Vector2D(this);
        scaled.scale(factor);
        return scaled;
    }

    Vector2D Vector2D::shifted(const Vector2D& offset) const {
        Vector2D shifted = Vector2D(this);
        shifted.shift(offset);
        return shifted;
    }

    int Vector2D::length() const {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

}