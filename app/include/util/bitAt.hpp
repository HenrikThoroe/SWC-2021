#pragma once

namespace Util {

    template<typename T, int size = sizeof(T)> T bitAt(T number, int pos) {
        if (pos < 0 || pos >= size * 8) {
            throw std::invalid_argument("Index not in range.");
        }

        return static_cast<T>(~(number >> ((size * 8 - 1) - pos))) % 2 == 0;
    }

}