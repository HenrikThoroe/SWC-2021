from typing import List

import os
import subprocess
import argparse

from pyblokustools.compileEngine import Compiler
from pyblokustools.helpers.coloring import Colors, colorT
from pyblokustools.helpers.platform import assertPlatform
from pyblokustools.version import VERSION

def runTests() -> None:
    assertPlatform()
    
    def parseOn_args(value: str) -> List[str]:
        return value.split()
    
    parser = argparse.ArgumentParser(
        prog='blokustest',
        description='Run all unittests for SWC-2021 Blokus.',
        epilog='Copyright (C) 2020 Rubin Raithel, Henrik Thorøe'
        )
    
    parser.version = f'BlokusTest v{VERSION}' # type: ignore
    
    parser.add_argument(
        '-v',
        '--version',
        action='version',
        help='display the current version'
        )
    parser.add_argument(
        '-a',
        '--all',
        action='store_true',
        help='recompile all files required',
        )
    parser.add_argument(
        '-d',
        '--debug',
        action='store_true',
        help='compile in debug mode',
        )
    parser.add_argument(
        '-F',
        '--forcelink',
        action='store_true',
        help='relink even if not outdated',
        )
    parser.add_argument(
        '-e',
        '--extraflags',
        action='store',
        type=parseOn_args,
        help='extra compiler flags',
        default=[]
        )
    parser.add_argument(
        '-t',
        '--testflags',
        action='store',
        type=parseOn_args,
        help='flags passed to the test',
        default=[]
        )
    
    args = parser.parse_args()

    print(colorT("Running unittests", Colors.WHITE))

    out_file = 'dist/tests.out'

    compiled: bool = Compiler.make(
        CWD           = os.getcwd(),
        outputFile    = out_file,
        sources_dir   = ['app/src', 'app/tests'],
        headers_dir   = ['app/include', 'app/tests'],
        extraExcludes = ['app/src/main.cpp'],
        debug         = args.debug,
        makeAll       = args.all,
        forceLink     = args.forcelink,
        extraFlags    = args.extraflags,
        sources_incRe = r".*/(?!Bench_)[^/]*$"
        )

    if not compiled:
        print(colorT("Tests will not be run as compilation failed", Colors.ORANGE))
        raise SystemExit()

    print(colorT("\nRunning tests:\n", Colors.PURPLE))
    os.execv(f'./{out_file}', ['testsRun.out' ,*args.testflags])
