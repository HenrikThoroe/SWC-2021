#include <stdexcept>

#include "loadAsset.hpp"

// Disable import warnings
#pragma diag_suppress 29

const char* XOR_NETWORK = 
    #include "xor_network.json.hpp"
;

#pragma endregion

namespace Util {

    const char* loadAsset(Asset asset) {
        if (asset == Asset::XOR_NETWORK) {
            return XOR_NETWORK;
        }

        throw std::runtime_error("Resource does not exist");
    }

}
