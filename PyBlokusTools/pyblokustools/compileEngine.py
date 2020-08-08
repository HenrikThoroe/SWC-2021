from __future__ import annotations
from typing import Optional, List, Dict, Union

import os
from pathlib import Path
import subprocess
import json

from .settings import Settings
from .helpers.hashing import Hasher
from .helpers.coloring import Colors, colorT

#? Compile settings to normalize paths
Settings.compileSettings()


class CompileCache():
    def __init__(self, fileHashes: Dict[str, str]={}):
        self.fileHashes = fileHashes #? Dict containing file->hash values to detect changes
    
    def dumps(self) -> str:
        """Dump the CompileCache instance to a string

        Returns:
            str -- JSON formatted CompilerCache
        """
        dump = {
            'fileHashes' : self.fileHashes
        }
        return json.dumps(dump)
    
    @staticmethod
    def loads(dump: str) -> CompileCache:
        """Load a CompileCache instance from a json dumo

        Arguments:
            dump {str} -- Dump as a string

        Returns:
            CompileCache -- Reconstructed instance
        """
        load = json.loads(dump)
        
        try:
            return CompileCache(**load)
        except:
            return CompileCache()
        
    
    def getChangedSourcesAndUpdate(self, currentFiles: List[str]) -> List[str]:
        """Get all source files that changed and update hashes internally

        Arguments:
            currentFiles {List[str]} -- Files to check

        Returns:
            List[str] -- List of all files that changed
        """
        ret = []
        
        for path in currentFiles:
            new_hash = Hasher.hash(path)
            if path not in self.fileHashes or not self.fileHashes[path] == new_hash:
                #? File not in cache
                #? File changed
                ret.append(path)
                self.fileHashes[path] = new_hash
            
        return ret
    
    def removeFileFromCache(self, path: str) -> bool:
        """Remove a file from the cache instance

        Arguments:
            path {str} -- File path to remove

        Returns:
            bool -- If file was present in cache
        """
        if path not in self.fileHashes:
            return False
        
        del self.fileHashes[path]
        return True

class Compiler():
    @staticmethod
    def gatherFiles(sourceDir: Union[str, List[str]], extension: str) -> List[str]:
        """Get all .cpp files in sourceDir

        Arguments:
            sourceDir {str} -- Path to sourcedir from current working directory
            extension {str} -- File extension to look for

        Returns:
            List[str] -- List of all files
        """
        if isinstance(sourceDir, list):
            ret = []
            for source in sourceDir:
                ret += [os.path.join(dirpath,filename) for dirpath, _, filenames in os.walk(source) for filename in filenames if filename.endswith(extension)]
            
            return ret
        
        return [os.path.join(dirpath,filename) for dirpath, _, filenames in os.walk(sourceDir) for filename in filenames if filename.endswith(extension)]
    
    @staticmethod
    def filterFiles(fileList: List[str], excludedFiles: List[str]) -> List[str]:
        """Filter out special files

        Arguments:
            fileList      {List[str]} -- Original file list
            excludedFiles {List[str]} -- List of files to exclude

        Returns:
            List[str] -- Filtered file list
        """
        return list(filter(lambda file: file not in excludedFiles, fileList))
    
    @staticmethod
    def normalizeFilePaths(fileList: List[str]) -> List[str]:
        """Normalize file paths

        Arguments:
            fileList {List[str]} -- Non normalized file path list

        Returns:
            List[str] -- List of normalized file paths
        """
        return [os.path.normpath(os.path.normcase(path)) for path in fileList]
    
    @staticmethod
    def make(
        CWD           : str,
        sources_dir   : Union[str, List[str]] = Settings.SOURCES_DIR,
        headers_dir   : Union[str, List[str]] = Settings.HEADERS_DIR,
        debug         : bool                  = False,
        makeAll       : bool                  = False,
        extraFlags    : List[str]             = [],
        extraExcludes : List[str]             = [],
        ) -> None:
        #? Init cache
        cache_dir = os.path.join(CWD, Settings.WORK_DIRECTORY)
        cache_file = os.path.join(cache_dir, Settings.CACHE_FILE)
        
        cache = None
        try:
            with open(cache_file, 'r') as file:
                cache = CompileCache.loads(file.read())
        except:
            cache = CompileCache()
        
        #? Normalize extraExcludes
        extraExcludes = Compiler.normalizeFilePaths(extraExcludes)
        
        #? Get files
        # Get all cpp files and filter them
        source_files = Compiler.filterFiles(
            Compiler.normalizeFilePaths(
                Compiler.gatherFiles(
                    sources_dir, Settings.SOURCES_EXT
                )
            ),
            [
                *extraExcludes,
                *(lambda: Settings.SOURCES_EXCLUDE_PROD if debug else Settings.SOURCES_EXCLUDE_DEBUG)()
            ]
        )
        
        # Determine which files need to be compiled
        to_compile = source_files if makeAll else cache.getChangedSourcesAndUpdate(source_files)
        
        # Get all hpp files and filter them
        header_files = Compiler.filterFiles(
            Compiler.normalizeFilePaths(
                Compiler.gatherFiles(
                    headers_dir, Settings.HEADERS_EXT
                )
            ),
            [
                *extraExcludes,
                *(lambda: Settings.HEADERS_EXCLUDE_PROD if debug else Settings.HEADERS_EXCLUDE_DEBUG)()
            ]
        )
        
        #? Filter out duplicate header directorys
        header_dirs = set()
        for header in header_files:
            pos = header.rfind('\\')
            if pos == -1:
                raise ValueError("HeaderFile is not in a subdirectory")
            
            header_dirs.add(header[:pos+1])
        
        #? Make shared compilation args
        comp_args = [
            *extraFlags,
            *Settings.COMP_SHARED_FLAGS,
            *(lambda: Settings.COMP_PROD_FLAGS if debug else Settings.COMP_DEBUG_FALGS)()
        ]
        
        #? Add header directorys to comp_args
        for header_dir in header_dirs:
            comp_args.append(f'-I{os.path.realpath(header_dir)}')
        
        #? Compile sourcefiles
        compiled_all_success = True
        with open(Settings.COMPILER_OUTPUT, "ab") as file:
            file.truncate(0) # Empty file for this compiler iteration
            
            compiled_out_dir = os.path.join(cache_dir, 'compiled')
            for source_file in to_compile:
                #Make sure output directory exists
                Path(os.path.join(compiled_out_dir, os.path.dirname(source_file))).mkdir(parents=True, exist_ok=True)

                proc = subprocess.run(
                    [
                        'g++',
                        *comp_args,
                        os.path.realpath(source_file),
                        '-o',
                        os.path.realpath(
                            os.path.join(
                                compiled_out_dir,
                                os.path.splitext(source_file)[0] + ".o"
                            )
                        )
                    ],
                    stdout=subprocess.PIPE,
                    stderr=subprocess.STDOUT
                    )
                file.write(proc.stdout)
                
                if proc.returncode != 0:
                    compiled_all_success = False
                    cache.removeFileFromCache(source_file)
        
        #? Dump cache      
        with open(cache_file, 'w') as file:
            file.write(cache.dumps())
        
        if compiled_all_success:
            print(colorT("Compilation finished successfully", Colors.GREEN))
        else:
            print(colorT("Compilation finished with errors", Colors.RED))
