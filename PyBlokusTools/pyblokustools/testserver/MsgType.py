from enum import Enum

class MsgType(Enum):
    """An enum of different message types.
    """
    JOINED      = 0
    WELCOME     = 1
    GAMESTATE   = 2
    MOVEREQUEST = 3
    LEFT        = 4
    RESULT      = 5
    EXCEPT      = 6
    PROTOCOLEND = 7
    UNDEFINED   = 8
