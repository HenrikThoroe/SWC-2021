#include <cmath>
#include <algorithm>

#include "Rect.hpp"

namespace Util {

    Rect::Rect(int minX, int maxX, int minY, int maxY) : minX(minX), maxX(maxX), minY(minY), maxY(maxY) {}

    int Rect::width() const {
        return maxX - minX + 1;
    }

    int Rect::height() const {
        return maxY - minY + 1;
    }

    float Rect::diagonal() const {
        return sqrtf(powf(static_cast<float>(width()), 2) + powf(static_cast<float>(height()), 2));
    }   

    Rect Rect::join(const Rect& other) const {
        return Rect(std::min(minX, other.minX), std::max(maxX, other.maxX), std::min(minY, other.minY), std::max(maxY, other.maxY));
    }

    int Rect::size() const {
        return width() * height();
    }

}
