from typing import overload, Final, Union, Callable, Tuple, Dict
from io import BufferedReader

import re
from functools import wraps
from pathlib import Path
from json import dump
from datetime import datetime

import logging
from tqdm import tqdm # type: ignore

def logger_enabled(func: Callable) -> Callable:
    """Decorator for only running when logging is actually enabled

    Arguments:
        func {Callable} -- Original Logger method
    
    Returns:
        Callable -- Active only Logger method
    """
    @wraps(func)
    def if_logger_enabled(self, *args, **kwargs) -> None:
        if self._enabled:
            func(self, *args, **kwargs)
    return if_logger_enabled

_ansi_escapeStr = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
_ansi_escapeByt = re.compile(rb'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
@overload
def filterAnsi(inp: str) -> str: ...
@overload
def filterAnsi(inp: bytes) -> bytes: ...
def filterAnsi(inp: Union[str, bytes]) -> Union[str, bytes]:
    """Filters all ANSI sequences from a text

    Arguments:
        inp {Union[str, bytes]} -- String/bytes with potential ANSI sequences

    Returns:
        Union[str, bytes] -- Cleaned string/bytes
    """
    if isinstance(inp, str):
        return _ansi_escapeStr.sub('', inp)
    elif isinstance(inp, bytes):
        return _ansi_escapeByt.sub(b'', inp)
    else:
        return inp

class ColoredFormatter(logging.Formatter):
    """Logging Formatter that colors the output
    """
    
    white    = "\033[38;21m"
    yellow   = "\033[33;21m"
    red      = "\033[31;21m"
    redBold  = "\033[31;1m"
    rst      = "\033[0m"
    
    formatNormal = "%(asctime)s %(levelname)s  %(name)s - %(message)s"
    formatError  = "%(asctime)s %(levelname)s  %(name)s - %(message)s (%(filename)s:%(lineno)d)"

    FORMATTERS: Dict[int, logging.Formatter] = {
        logging.DEBUG:    logging.Formatter(fmt=white    + formatNormal + rst, datefmt='%H:%M:%S'),
        logging.INFO:     logging.Formatter(fmt=white    + formatNormal + rst, datefmt='%H:%M:%S'),
        
        logging.WARNING:  logging.Formatter(fmt=yellow   + formatError  + rst, datefmt='%H:%M:%S'),
        logging.ERROR:    logging.Formatter(fmt=red      + formatError  + rst, datefmt='%H:%M:%S'),
        logging.CRITICAL: logging.Formatter(fmt=redBold  + formatError  + rst, datefmt='%H:%M:%S'),
    }

    def format(self, record: logging.LogRecord) -> str:
        """Format a LogRecord for output

        Arguments:
            record {logging.LogRecord} -- LogRecord from event to output

        Returns:
            str -- Formatted LogRecord ready to output
        """
        return ColoredFormatter.FORMATTERS[record.levelno].format(record)

class Logger(logging.Handler):
    """Logger used for all logging and file log handling

    Arguments:
        clientNames {Tuple[str, str]} -- Names of clients
        enabled     {bool}            -- Logging enabled
        level       {int}             -- Log level to use (default: logging.INFO)
    """
    def __init__(self, clientNames: Tuple[str, str], enabled: bool = True, level: int = logging.INFO) -> None:
        super().__init__(level) # Set logger level
        
        self._clientNames: Final[Tuple[str, str]] = clientNames
        self._enabled                             = enabled

        self.subfolder = 0 # Used to determine which game is currently logged
        self._folder   = "" # Folder of current game logs
        
        now            = datetime.now()
        self._dirName  = f'./massLogs/{now.month}-{now.day}-{now.year}_{now.hour}-{now.minute}' # Root folder for this runs logs
        Path(self._dirName).mkdir(parents=True, exist_ok=True)
        
        if enabled:
            self.setFormatter(ColoredFormatter())
    
    @logger_enabled
    def emit(self, record: logging.LogRecord) -> None:
        """Handler for actual logging calls

        Arguments:
            record {logging.LogRecord} -- A logging event
        """
        try:
            #? Add game info if games already started
            if self._folder != "":
                record.msg += f" (Subfolder: {self.subfolder})"
            
            msg = self.format(record)
            tqdm.write(msg)
            
            #? Write all logs Warning >= to main log file
            if record.levelno >= 30:
                self.logFile(msg+'\n')
            
            self.flush()
        except (KeyboardInterrupt, SystemExit):
            raise
        except:
            self.handleError(record)

    @logger_enabled
    def makeDirs(self) -> None:
        """Calculate log file paths and create folders (Call before every game)
        """
        while True:
            if not Path(f'{self._dirName}/{self.subfolder}').exists():
                break
            self.subfolder += 1

        path = Path(f'{self._dirName}/{self.subfolder}').resolve()
        path.mkdir(parents=True, exist_ok=True)
        self._folder = path.as_posix()

    @logger_enabled
    def logClient(self, client: int, log: BufferedReader) -> None:
        """Log a clients stdout and stderr to the right file

        Arguments:
            client {int}            -- Client id (0/1)
            log    {BufferedReader} -- Stdout attribute of proccess
        """
        with open(f'{self._folder}/{self._clientNames[client]}.txt', 'ab') as file:
            file.write(filterAnsi(log.read() or b''))
    
    @logger_enabled
    def logServer(self, log: BufferedReader) -> None:
        """Copy current server log to specific folder and main log
        
        Arguments:
            log    {BufferedReader} -- Stdout attribute of proccess
        """
        filtered_log = filterAnsi(log.read() or b'')
        
        #* Specific game
        with open(f'{self._folder}/server.txt', 'ab') as file:
            file.write(filtered_log)
        
        #* Main log
        with open(f'{self._dirName}/server.txt', 'ab') as file:
            file.write(filtered_log)
    
    @logger_enabled
    def logFile(self, message: str) -> None:
        """Log any message to the main log file

        Arguments:
            message {str} -- Message to write
        """
        with open(f'{self._dirName}/log.txt', 'a') as file:
            file.write(filterAnsi(message))
    
    @logger_enabled
    def logJSONFile(self, message: dict) -> None:
        """Write any JSON serializable dict to the main JSON log file

        Arguments:
            message {dict} -- Message to write
        """
        with open(f'{self._dirName}/log.json', 'w') as file:
            dump(message, file)
