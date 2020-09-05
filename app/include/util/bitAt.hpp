#pragma once

namespace Util {

    /**
     * @brief Returns the bit at `pos` of `number`
     * @throw Throws an exception if `pos` is not in range 0 ..< sizeof(number) * 8
     */
    template<typename T, int size = sizeof(T)> T bitAt(T number, int pos) {
        if (pos < 0 || pos >= size * 8) {
            throw std::invalid_argument("Index not in range.");
        }

        return static_cast<T>(~(number >> ((size * 8 - 1) - pos))) % 2 == 0;
    }

}