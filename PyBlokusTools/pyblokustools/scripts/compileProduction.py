from typing import List

import os
import subprocess
import argparse
import zipfile

from pyblokustools.compileEngine import Compiler
from pyblokustools.helpers.coloring import Colors, colorT
from pyblokustools.helpers.platform import assertPlatform
from pyblokustools.version import VERSION

def compileProduction() -> None:
    assertPlatform()
    
    def parseOn_args(value: str) -> List[str]:
        return value.split()
    
    parser = argparse.ArgumentParser(
        prog='blokusprod',
        description='Compile SWC-2021 Blokus in production mode.',
        epilog='Copyright (C) 2020 Rubin Raithel, Henrik Thorøe'
        )
    
    parser.version = f'BlokusProd v{VERSION}' # type: ignore
    
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
        '-S',
        '--sourcesdirs',
        action='store',
        type=parseOn_args,
        help='directories to look for source files',
        default=['app/src']
        )
    parser.add_argument(
        '-H',
        '--headersdirs',
        action='store',
        type=parseOn_args,
        help='directories to look for header files',
        default=['app/include']
        )
    parser.add_argument(
        '-x',
        '--excludes',
        action='store',
        type=parseOn_args,
        help='files to specifically exclude',
        default=[]
        )
    parser.add_argument(
        '-sre',
        '--sourcesincre',
        action='store',
        type=str,
        help='regex of valid source files',
        default="."
        )
    parser.add_argument(
        '-hre',
        '--headersincre',
        action='store',
        type=str,
        help='regex of valid header files',
        default="."
        )
    
    args = parser.parse_args()

    print(colorT("Compiling in production mode", Colors.WHITE))

    out_file = 'dist/prod.out'

    compiled: bool = Compiler.make(
        CWD           = os.getcwd(),
        outputFile    = out_file,
        sources_dir   = args.sourcesdirs,
        headers_dir   = args.headersdirs,
        extraExcludes = args.excludes,
        debug         = False,
        makeAll       = args.all,
        forceLink     = args.forcelink,
        extraFlags    = list(set(args.extraflags) | {'-march=broadwell', '-DNOLOG'}),
        sources_incRe = args.sourcesincre,
        headers_incRe = args.headersincre,
        )

    if not compiled:
        print(colorT("Could not compile, please see 'compilerOutput.txt'", Colors.ORANGE))
        raise SystemExit()

    print(colorT("\nCompiled successfully, placed in 'dist/'", Colors.GREEN))

    zipf = zipfile.ZipFile('dist/client.zip', 'w', zipfile.ZIP_DEFLATED)
    zipf.write(os.path.abspath('start.sh'), '/start.sh')
    zipf.write(os.path.abspath('dist/prod.out'), 'dist/prod.out')
    failedFiles = zipf.testzip()
    zipf.close()

    if failedFiles:
        print(colorT("\nFailed to compress files. Error in: {}".format(str.join(", ", failedFiles)), Colors.RED))
        raise SystemExit()

    print(colorT("Compressed successfully, placed in 'dist/'", Colors.GREEN))
