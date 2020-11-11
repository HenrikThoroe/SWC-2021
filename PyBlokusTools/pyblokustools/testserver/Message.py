from typing import Any, Final, Tuple
from enum import Enum

from .MsgType import MsgType

class Message():
    """Base Message

    Arguments:
        type    {MsgType} -- Type of message
        payload {Any}     -- Payload used for later handling
    """
    def __init__(self, type: MsgType, payload: Any) -> None:
        self.type:    Final[MsgType] = type
        self.payload: Final[Any]     = payload
    
    def __repr__(self) -> str:
        """Represent object instance

        Returns:
            str -- Representation of instance
        """
        return f"Message({self.type}, {self.payload})"

class MementoMsg():
    """Message that holds a Gamestate

    Arguments:
        currentTurn {int} -- Current turn
    """
    def __init__(self, currentTurn: int) -> None:
        self.currentTurn: Final[int] = currentTurn
    
    def __repr__(self) -> str:
        """Represent object instance

        Returns:
            str -- Representation of instance
        """
        return f"MementoMsg({self.currentTurn})"

class ResultCause(Enum):
    """An enum of different game end causes.
    """
    REGULAR        = 0
    LEFT           = 1
    RULE_VIOLATION = 2
    SOFT_TIMEOUT   = 3
    HARD_TIMEOUT   = 4

class ResultEnd(Enum):
    """An enum of different game endings.
    """
    LOSE = 0
    DRAW = 1
    WIN  = 2

class ResultMsg():
    """Message that holds a game's result

    Arguments:
        score {Tuple[int, int]}                 -- GameScore both players reached
        end   {Tuple[ResultEnd, ResultEnd]}     -- TournamentPoints both players earned
        cause {Tuple[ResultCause, ResultCause]} -- Game-ending causes for both players
    """
    def __init__(self, score: Tuple[int, int], end: Tuple[ResultEnd, ResultEnd], cause: Tuple[ResultCause, ResultCause]) -> None:
        self.score: Final[Tuple[int, int]]                 = score
        self.end:   Final[Tuple[ResultEnd, ResultEnd]]     = end
        self.cause: Final[Tuple[ResultCause, ResultCause]] = cause
    
    def __repr__(self) -> str:
        """Represent object instance

        Returns:
            str -- Representation of instance
        """
        return f"ResultMsg(({self.score[0]}, {self.score[1]}), ({self.end[0]}, {self.end[1]}), ({self.cause[0]}, {self.cause[1]}))"

class PreparedMsg():
    """Message that holds info on a prepared game

    Arguments:
        roomId       {str}       -- RoomId of newly prepared game
        reservations {Tuple[str]} -- Reservation codes for clients associated with the game
    """
    def __init__(self, roomId: str, reservations: Tuple[str]) -> None:
        self.roomId:       Final[str]        = roomId
        self.reservations: Final[Tuple[str]] = reservations
    
    def __repr__(self) -> str:
        """Represent object instance

        Returns:
            str -- Representation of instance
        """
        return f"PreparedMsg({self.roomId}, ({self.reservations[0]}, {self.reservations[1]}))"