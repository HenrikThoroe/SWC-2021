from typing import Optional, List

import os
from pathlib import Path
import subprocess

from .settings import Settings
from .helpers.hashing import Hasher


class CompileCache():
    def __init__(self):
        self.fileHashes = {} #? Dict containing file->hash values to detect changes
    
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
        

class Compiler():
    @staticmethod
    def gatherFiles(sourceDir: str, extension: str) -> List[str]:
        """Get all .cpp files in sourceDir

        Arguments:
            sourceDir {str} -- Path to sourcedir from current working directory
            extension {str} -- File extension to look for

        Returns:
            List[str] -- List of all files
        """
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
        return list(filter(lambda file: os.path.normpath(file) not in excludedFiles, fileList))
    
    @staticmethod
    def normalizeFilePaths(fileList: List[str]) -> List[str]:
        """Normalize file paths

        Arguments:
            fileList {List[str]} -- Non normalized file path list

        Returns:
            List[str] -- List of normalized file paths
        """
        return [os.path.normpath(path) for path in fileList]
    
    @staticmethod
    def make(CWD: str, debug: bool=False, cache: Optional[CompileCache]=None, makeAll: bool=False) -> None:
        cache_dir = os.path.join(CWD, Settings.WORK_DIRECTORY)
        # Init cache
        cache = cache if cache else CompileCache()
        
        # Get all cpp files and filter them
        source_files = Compiler.normalizeFilePaths(
            Compiler.filterFiles(
                Compiler.gatherFiles(
                    Settings.SOURCES_DIR, Settings.SOURCES_EXT
                ),
                Settings.SOURCES_EXCLUDE_PROD if debug else Settings.SOURCES_EXCLUDE_DEBUG
            )
        )
        
        to_compile = source_files if makeAll else cache.getChangedSourcesAndUpdate(source_files)
        
        header_files = Compiler.normalizeFilePaths(
            Compiler.filterFiles(
                Compiler.gatherFiles(
                    Settings.HEADERS_DIR, Settings.HEADERS_EXT
                ),
                Settings.HEADERS_EXCLUDE_PROD if debug else Settings.HEADERS_EXCLUDE_DEBUG
            )
        )
        
        header_dirs = set()
        for header in header_files:
            pos = header.rfind('\\')
            if pos == -1:
                raise ValueError("HeaderFile is not in a subdirectory")
            
            header_dirs.add(header[:pos+1])
        
        comp_args = [*Settings.COMP_SHARED_FLAGS, *(lambda: Settings.COMP_PROD_FLAGS if debug else Settings.COMP_DEBUG_FALGS)()]
        
        #? Add header directorys to comp_args
        for header_dir in header_dirs:
            comp_args.append(f'-I{os.path.realpath(header_dir)}')
        
        #? Build main compile_command
        compile_command_root = 'g++ ' + ' '.join(comp_args)
        
        #? Map sourcefiles to compile_command_root
        with open(Settings.COMPILER_OUTPUT, "ab") as file:
            file.truncate(0) # Empty file for this compiler iteration
            
            compiled_out_dir = os.path.join(cache_dir, 'compiled')
            for source_file in to_compile:
                #Make sure output directory exists
                Path(os.path.join(compiled_out_dir, os.path.dirname(source_file))).mkdir(parents=True, exist_ok=True)
                
                comp_cmd = f'{compile_command_root} {os.path.realpath(source_file)} -o {os.path.realpath(os.path.join(compiled_out_dir, os.path.splitext(source_file)[0] + ".o"))}'
            
                file.write(subprocess.Popen(comp_cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT).stdout.read())
