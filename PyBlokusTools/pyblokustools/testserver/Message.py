from typing import Any, Final, Tuple
from enum import Enum

from .MsgType import MsgType

class Message():
    def __init__(self, type: MsgType, payload: Any) -> None:
        self.type:    Final[MsgType] = type
        self.payload: Final[Any]     = payload

class MementoMsg():
    def __init__(self, currentTurn: int) -> None:
        """Construct a new MementoMsg

        Arguments:
            currentTurn {int} -- Current turn
        """
        self.currentTurn: Final[int] = currentTurn

class ResultMsg():
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
    
    def __init__(self, score: Tuple[int, int], end: Tuple[ResultEnd, ResultEnd], cause: Tuple[ResultCause, ResultCause]) -> None:
        """Construct a new ResultMsg

        Arguments:
            score {Tuple[int, int]}                 -- GameScore both players reached
            end   {Tuple[ResultEnd, ResultEnd]}     -- TournamentPoints both players earned
            cause {Tuple[ResultCause, ResultCause]} -- Game-ending causes for both players
        """
        self.score: Final[Tuple[int, int]]                 = score
        self.end:   Final[Tuple[ResultEnd, ResultEnd]]     = end
        self.cause: Final[Tuple[ResultCause, ResultCause]] = cause
