from typing import List

import argparse
import re
from datetime import timedelta

from pyblokustools.testserver.TestServer import TestServer
from pyblokustools.helpers.coloring import Colors, colorT
from pyblokustools.helpers.platform import assertPlatform
from pyblokustools.version import VERSION

def massTest() -> None:
    assertPlatform()
    
    def parseOn_args(value: str) -> List[str]:
        return value.split()
    
    def parseLoglvl_args(value: str) -> int:
        switch = {
            "CRITICAL" : 50,
            "FATAL"    : 50,
            "ERROR"    : 40,
            "WARNING"  : 30,
            "WARN"     : 30,
            "INFO"     : 20,
            "DEBUG"    : 10,
            "NOTSET"   : 0,
        }
        if value not in switch:
            print(colorT(f"Invalid log level '{value}'", Colors.YELLOW))
        return switch[value]
    
    def parseStrip_args(value: str) -> str:
        return value.strip()
    
    def parse_time(time_str: str) -> timedelta:
        """Modified from https://stackoverflow.com/a/4628148/851699
        """
        time_regex = re.compile(r'^((?P<days>[\.\d]+?)d)?((?P<hours>[\.\d]+?)h)?((?P<minutes>[\.\d]+?)m)?((?P<seconds>[\.\d]+?)s)?$')
        
        parts = time_regex.match(time_str)
        if parts is None:
            print(colorT(f"Invalid time string '{time_str}'", Colors.YELLOW))
            
        time_params = {name: float(param) for name, param in parts.groupdict().items() if param}
        return timedelta(**time_params)
    
    parser = argparse.ArgumentParser(
        prog='blokusmass',
        description='Mass test two SWC-2021 clients.',
        epilog='Copyright (C) 2020 Rubin Raithel, Henrik Thorøe'
        )
    
    parser.version = f'BlokusMass v{VERSION}' # type: ignore
    
    parser.add_argument(
        '-v',
        '--version',
        action='version',
        help='display the current version'
        )
    parser.add_argument(
        '-c1',
        '--client1',
        action='store',
        type=str,
        help='path to client1 executable',
        )
    parser.add_argument(
        '-c2',
        '--client2',
        action='store',
        type=str,
        help='path to client2 executable',
        )
    parser.add_argument(
        '-c1n',
        '--client1name',
        action='store',
        type=parseStrip_args,
        help='name of client1',
        default="Client1"
        )
    parser.add_argument(
        '-c2n',
        '--client2name',
        action='store',
        type=parseStrip_args,
        help='name of client2',
        default="Client2"
        )
    parser.add_argument(
        '-c1a',
        '--client1args',
        action='store',
        type=parseOn_args,
        help='extra arguments to start client1 with',
        default=[]
        )
    parser.add_argument(
        '-c2a',
        '--client2args',
        action='store',
        type=parseOn_args,
        help='extra arguments to start client2 with',
        default=[]
        )
    parser.add_argument(
        '-c1nt',
        '--client1noTimeout',
        action='store_true',
        help='disable timeouts for client1',
    )
    parser.add_argument(
        '-c2nt',
        '--client2noTimeout',
        action='store_true',
        help='disable timeouts for client1',
    )
    parser.add_argument(
        '-p',
        '--port',
        action='store',
        type=int,
        help='port the server should run on',
        default=13055
        )
    parser.add_argument(
        '-i',
        '--iterations',
        action='store',
        type=int,
        help='how many games should be played',
        default=None
    )
    parser.add_argument(
        '-t',
        '--time',
        action='store',
        type=parse_time,
        help='how long the tests should run eg. 2d12h43m20s',
        default=None
    )
    parser.add_argument(
        '-nl',
        '--nolog',
        action='store_true',
        help='disable logging',
        )
    parser.add_argument(
        '-l',
        '--loglevel',
        action='store',
        type=parseLoglvl_args,
        help='log level to print to the console',
        default=20
    )
    parser.add_argument(
        '-j',
        '--jsonlogs',
        action='store_true',
        help='enable JSON logs for automated analysis',
    )
    
    args = parser.parse_args()
    
    if args.iterations is None and args.time is None:
        print(colorT("Please specify iterations or time", Colors.YELLOW))
        raise SystemExit()
    
    if args.client1name == args.client2name:
        print(colorT("Please name the clients uniquely", Colors.YELLOW))
        raise SystemExit()

    massTests = TestServer(
        clients           = (args.client1, args.client2),
        clientNames       = (args.client1name, args.client2name),
        clientArguments   = (args.client1args, args.client2args),
        clientsCanTimeout = (not args.client1noTimeout, not args.client2noTimeout),
        serverPort        = args.port,
        logEnabled        = not args.nolog,
        logLevel          = args.loglevel,
        jsonLogs          = args.jsonlogs,
        )
    
    massTests.run(
        iterations = args.iterations,
        deltatime  = args.time,
    )
