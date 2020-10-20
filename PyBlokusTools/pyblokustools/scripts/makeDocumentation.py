from typing import List

import os
import subprocess
import argparse

from pyblokustools.helpers.coloring import Colors, colorT
from pyblokustools.helpers.platform import assertPlatform
from pyblokustools.settings import Settings
from pyblokustools.version import VERSION

def makeDocumentation() -> None:
    assertPlatform()
    
    def parseOn_args(value: str) -> List[str]:
        return value.split()
    
    parser = argparse.ArgumentParser(
        prog='blokusdoc',
        description='Make all docs for SWC-2021 Blokus.',
        epilog='Copyright (C) 2020 Rubin Raithel, Henrik Thorøe'
        )
    
    parser.version = f'BlokusDoc v{VERSION}' # type: ignore
    
    parser.add_argument(
        '-v',
        '--version',
        action='version',
        help='display the current version'
        )
    
    args = parser.parse_args()

    print(colorT("Making docs", Colors.WHITE))

    with open(Settings.COMPILER_OUTPUT, "wb") as logFile:
        proc1 = subprocess.run(
                [
                    'doxygen',
                ],
                cwd="./docsrc",
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT
            )
        logFile.write(proc1.stdout)
        if proc1.returncode != 0:
            print(colorT("\nCould not make Doxygen-Docs, please check 'compilerOutput.txt'", Colors.RED))
            raise SystemExit()
        
        logFile.write(b"\n\n\n\n")
        
        proc2 = subprocess.run(
                [
                    'make',
                    'github'
                ],
                cwd="./docsrc",
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT
            )
        logFile.write(proc2.stdout)
        if proc2.returncode != 0:
            print(colorT("\nCould not make Sphinx-Docs, please check 'compilerOutput.txt'", Colors.RED))
            raise SystemExit()
    
    print(colorT("\nDocs made successfully, placed in 'docs/'", Colors.GREEN))
