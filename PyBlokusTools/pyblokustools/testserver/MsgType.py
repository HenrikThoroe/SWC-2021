from enum import Enum

class MsgType(Enum):
    """An enum of different message types.
    """
    GAMESTATE   = 0
    LEFT        = 1
    RESULT      = 2
    EXCEPT      = 3
    PREPARED    = 4
    OBSERVED    = 5
    PROTOCOLEND = 6
    CLOSECONN   = 7
    UNDEFINED   = 8
