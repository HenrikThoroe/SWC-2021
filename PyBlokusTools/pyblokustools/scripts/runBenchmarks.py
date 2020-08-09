from typing import List

import os
import subprocess
import argparse

from pyblokustools.compileEngine import Compiler
from pyblokustools.helpers.coloring import Colors, colorT
from pyblokustools.helpers.platform import assertPlatform
from pyblokustools.version import VERSION

def runBenchmarks() -> None:
    assertPlatform()
    
    def parseOn_args(value: str) -> List[str]:
        return value.split()
    
    parser = argparse.ArgumentParser(
        prog='blokusbench',
        description='Run all benchmarks for SWC-2021 Blokus.',
        epilog='Copyright (C) 2020 Rubin Raithel, Henrik Thorøe'
        )
    parser.version = f'BlokusBench v{VERSION}' # type: ignore
    
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
        '-b',
        '--benchflags',
        action='store',
        type=parseOn_args,
        help='flags passed to the benchmark',
        default=[]
        )
    
    args = parser.parse_args()

    print(colorT("Trying to run benchmarks", Colors.WHITE))
    print(colorT("Compiling first:\n", Colors.PURPLE))

    out_file = 'dist/benchmarksRun.out'

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
        sources_incRe = r".*/(?!Test_)[^/]*$"
        )

    if not compiled:
        print(colorT("Benchmarks will not be run as compilation failed", Colors.ORANGE))
        raise SystemExit()

    print(colorT("\nRunning benchmarks:\n", Colors.PURPLE))
    subprocess.run(
            [
                f'./{out_file}',
                *args.testflags
            ],
            stderr=subprocess.STDOUT
        )
