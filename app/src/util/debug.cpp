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

    void debugPrint(const Model::DeployedPiece* piece) {
        #ifdef DEBUG
        if (piece == nullptr) {
            std::cout << "Skip Move" << std::endl;
        } else {
            std::cout << *piece << std::endl;
        }
        #endif
    }

    void debugPrint(const Model::DeployedPiece& piece) {
        #ifdef DEBUG
        std::cout << piece << std::endl;
        #endif
    }
} 
