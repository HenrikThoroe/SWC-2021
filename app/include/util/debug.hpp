#pragma once

#ifdef DEBUG
#include <iostream>
#endif
#include <string>

#include "DeployedPiece.hpp"

namespace Util
{
    /**
     * @brief Print something only in debug mode
     * 
     * @param str A pointer to a string to print
     */
    void debugPrint(std::string* str);

    /**
     * @brief Print something only in debug mode
     * 
     * @param str A string to print
     */
    void debugPrint(std::string str);

    void debugPrint(const Model::DeployedPiece* piece);

    void debugPrint(const Model::DeployedPiece& piece);
}
