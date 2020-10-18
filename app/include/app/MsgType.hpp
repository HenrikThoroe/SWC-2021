#pragma once

#include <inttypes.h>

namespace App {

    /// An enum of different message types.
    /// @note types map to uint8_t
    enum class MsgType: uint8_t {
        JOINED      = 0, 
        WELCOME     = 1,
        GAMESTATE   = 2, 
        MOVEREQUEST = 3,
        LEFT        = 4, 
        RESULT      = 5,
        EXCEPT      = 6, 
        PROTOCOLEND = 7,
        UNDEFINED   = 8
    };
    
}