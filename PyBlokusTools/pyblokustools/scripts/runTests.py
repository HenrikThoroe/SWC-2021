import os
import argparse

from pyblokustools.compileEngine import Compiler
from pyblokustools.helpers.coloring import Colors, colorT
from pyblokustools.helpers.platform import assertPlatform
from pyblokustools.version import VERSION

def runTests() -> None:
    assertPlatform()
    
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
    
    args = parser.parse_args()

    print(colorT("Trying to run unittests", Colors.WHITE))
    print(colorT("Compiling first:\n", Colors.PURPLE))

    out_file = 'dist/testsRun.out'

    compiled: bool = Compiler.make(os.getcwd(), out_file, ['app/src', 'app/tests'], ['app/include', 'app/tests'], extraExcludes=['app/src/main.cpp'], makeAll=args.all)

    if not compiled:
        print(colorT("Tests will not be run as compilation failed", Colors.ORANGE))
        raise SystemExit()

    print(colorT("\nRunning tests:\n", Colors.PURPLE))
    os.system(f'./{out_file}')
