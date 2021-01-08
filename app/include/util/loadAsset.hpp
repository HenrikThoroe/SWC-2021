#pragma once

#include <string>

namespace Util {

    enum class Asset {
        XOR_NETWORK
    };

    const char* loadAsset(Asset asset);

}
