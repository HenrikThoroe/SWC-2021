#include <math.h>

#include "Vector2D.hpp"

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

    double Vector2D::length() const {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    Vector2D Vector2D::operator + (const Vector2D& offset) const {
        return shifted(offset);
    }

    Vector2D Vector2D::operator * (const int& factor) const {
        return scaled(factor);
    }

    bool Vector2D::operator == (const Vector2D& other) const{
        return x == other.x && y == other.y;
    }

    std::ostream& operator << (std::ostream& os, const Vector2D& vec) {
        os << "Vector2D { x: " << vec.x << ", y: " << vec.y << " }";
        return os;
    }

}