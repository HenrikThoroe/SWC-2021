#include <cmath>

#include "Vector2D.hpp"

namespace Util {

    Vector2D::Vector2D() : Vector2D(0, 0) {}

    Vector2D::Vector2D(int8_t x, int8_t y) : x(x), y(y) {};

    Vector2D::Vector2D(const Vector2D& other) : x(other.x), y(other.y) {};

    Vector2D::Vector2D(const Vector2D* other) : x(other->x), y(other->y) {};

    void Vector2D::scale(const int8_t& factor) {
        x *= factor;
        y *= factor;
    }

    void Vector2D::shift(const Vector2D& other) {
        x += other.x;
        y += other.y;
    }

    Vector2D Vector2D::scaled(const int8_t& factor) const {
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
        return std::sqrt(std::pow(x, 2) + std::pow(y, 2));
    }

    Vector2D Vector2D::operator + (const Vector2D& offset) const {
        return shifted(offset);
    }

    Vector2D Vector2D::operator * (const int8_t& factor) const {
        return scaled(factor);
    }

    Vector2D Vector2D::operator - (const Vector2D& sub) const {
        return Vector2D(x - sub.x, y - sub.y);
    }

    Vector2D Vector2D::operator - () const {
        return Vector2D(-x, -y);
    }

    bool Vector2D::operator == (const Vector2D& other) const{
        return x == other.x && y == other.y;
    }

    std::ostream& operator << (std::ostream& os, const Vector2D& vec) {
        os << "Vector2D { x: " << static_cast<int>(vec.x) << ", y: " << static_cast<int>(vec.y) << " }";
        return os;
    }

}
