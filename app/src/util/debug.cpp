#include "debug.hpp"

namespace Util
{
    void debugPrint(std::string* str) {
        #ifdef DEBUG
        std::cout << *str << std::endl;
        #endif
    }

    void debugPrint(std::string str) {
        #ifdef DEBUG
        std::cout << str << std::endl;
        #endif
    }
} // namespace Util
