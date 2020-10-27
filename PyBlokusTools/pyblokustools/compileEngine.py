from __future__ import annotations
from typing import Optional, List, Dict, Tuple, Union, IO

import os
from pathlib import Path
import subprocess
import json
import re

from .settings import Settings
from .helpers.hashing import Hasher
from .helpers.coloring import Colors, colorT

#? Compile settings to normalize paths
Settings.compileSettings()


class CompileCache():
    def __init__(
        self,
        fileHashes: Dict[str, Tuple[str, str, List[str], Dict[str, str]]]={},
        linkFilesHashes: Dict[str, str]={}
    ) -> None:
        #? Dict containing file->hash values to detect changes (path->[lastCompiledFileHash, lastCompiledCompArgsHash, [outputFile], {headerName->lastCompiledFileHash(for Header)}])
        self.fileHashes                = fileHashes
        #? List containing all source files that need to be updated after successfull linking
        self.pendingLinkage: List[str] = []
        #? Dict containing outputFile->LastLinkFilesListHash
        self.linkFilesHashes           = linkFilesHashes
    
    def dumps(self) -> str:
        """Dump the CompileCache instance to a string

        Returns:
            str -- JSON formatted CompilerCache
        """
        dump = {
            'fileHashes'      : self.fileHashes,
            'linkFilesHashes' : self.linkFilesHashes,
        }
        return json.dumps(dump)
    
    @staticmethod
    def loads(dump: str) -> CompileCache:
        """Load a CompileCache instance from a json dump

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
    
    def getChangedSourcesAndUpdate(self, currentFiles: List[str], header_files: List[str], compArgsHash: str) -> List[str]:
        """Get all source files that changed and update hashes internally

        Arguments:
            currentFiles {List[str]} -- Files to check
            header_files {List[str]} -- Header files to include
            compArgsHash {str}       -- Hash of shared compilation args

        Returns:
            List[str] -- List of all files that changed
        """
        ret = []
        
        for path in currentFiles:
            new_hash = Hasher.hashFile(path)
            if (
                path not in self.fileHashes
                or not self.fileHashes[path][0] == new_hash
                or not self.fileHashes[path][1] == compArgsHash
                ):
                #? File not in cache
                #? File changed
                #? Compilation args changed
                ret.append(path)
                self.fileHashes[path] = (new_hash, compArgsHash, [])
            
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

    def needsNewLinking(self, sourceFiles: List[str], outputFile: str) -> bool:
        """Check if new linking is required, run `AFTER` getChangedSourcesAndUpdate

        Arguments:
            sourceFiles {List[str]} -- `ALL` source files
            outputFile  {str}       -- Path of output binary

        Returns:
            bool -- Needs new linking
        """
        ret = False
        
        sourceFilesHash = Hasher.hashList(sourceFiles)
        
        for path in sourceFiles:
            if (
                outputFile not in self.fileHashes[path][2]
                or outputFile not in self.linkFilesHashes
                or self.linkFilesHashes[outputFile] != sourceFilesHash
                ):
                #? Not yet linked with file
                #? Never linked before
                #? Not linked with combination of files
                ret = True
                self.pendingLinkage.append(path)
        
        if ret:
            self.linkFilesHashes[outputFile] = sourceFilesHash
        
        return ret

    def commitPendingLinkage(self, outputFile: str) -> None:
        """Update state of all files that were pending linking

        Arguments:
            outputFile {str} -- Path of output binary
        """
        for path in self.pendingLinkage:
            self.fileHashes[path][2].append(outputFile)
    
class Compiler():
    @staticmethod
    def gatherFiles(sourceDir: Union[str, List[str]], extension: str) -> List[str]:
        """Get all .extension files in sourceDir

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
    def filterFilesRe(fileList: List[str], includeRe: str) -> List[str]:
        """Filter all fileNAMES and only keep those that match the regular expression

        Arguments:
            fileList  {List[str]} -- Original file list
            includeRe {str}       -- Regular expression of fileNAMES to keep

        Returns:
            List[str] -- Filtered file list
        """
        return list(filter(lambda file: bool(re.match(includeRe, file)), fileList))
    
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
    def validateHeaders(fileList: List[str]) -> List[str]:
        """Check if all HeaderFiles are valid

        Arguments:
            fileList {List[str]} -- Normalized header file paths

        Returns:
            Tuple[List[str], List[str]] -- Tuple[sameNameList, noPragmaOnceList]
        """
        errorsRet: Tuple[List[str], List[str]] = []
        baseNames: List[str] = []
        
        for header in fileList:
            #? Check same name
            base = os.path.basename(header)
            if base not in baseNames:
                baseNames.append(os.path.basename(header))
            else:
                errorsRet[0].append(header)
                
                # Filter out multpile headers with the same name
                i = 0
                while True:
                    try:
                        i = baseNames.index(base, start=i)
                        errorsRet[0].append(fileList[i])
                        i += 1
                    except:
                        break
            
            #? Check pragma once
            commentFlag = False
            with open(header, "r") as file:
                for line in file:
                    test = line.strip()
                    
                    if test == "" or (len(test) > 1 and test[:2] == "//"):
                        continue
                    
                    if len(test) > 2 and test[:3] == "/**":
                        commentFlag = True
                        continue
                    
                    if commentFlag:
                        if len(test) > 0 and test[:1] == "*":
                            continue
                        if len(test) > 1 and test[:2] == "*/":
                            commentFlag = False
                            continue
                    
                    if test != "#pragma once":
                        errorsRet[1].append(header)
                    
                    break
        
    
    @staticmethod
    def make(
        CWD           : str,
        outputFile    : str,
        sources_dir   : Union[str, List[str]] = Settings.SOURCES_DIR,
        headers_dir   : Union[str, List[str]] = Settings.HEADERS_DIR,
        debug         : bool                  = False,
        makeAll       : bool                  = False,
        forceLink     : bool                  = False,
        extraFlags    : List[str]             = [],
        extraExcludes : List[str]             = [],
        sources_incRe : str                   = r'.',
        headers_incRe : str                   = r'.',
    ) -> bool:
        #? Init cache
        cache_dir = os.path.join(CWD, Settings.WORK_DIRECTORY)
        cache_file = os.path.join(cache_dir, Settings.CACHE_FILE)
        
        cache = None
        try:
            with open(cache_file, 'r') as file:
                cache = CompileCache.loads(file.read())
        except:
            cache = CompileCache()
        
        #? Make shared compilation args
        comp_args = [
            *extraFlags,
            *Settings.COMP_SHARED_FLAGS,
            *(lambda: Settings.COMP_DEBUG_FALGS if debug else Settings.COMP_PROD_FLAGS)()
        ]
        # Compute shared compilation args hash
        comp_args_hash = Hasher.hashList(comp_args)
        
        #? Normalize extraExcludes
        extraExcludes = Compiler.normalizeFilePaths(extraExcludes)
        
        #? Get files
        # Get all cpp files and filter them
        source_files = Compiler.filterFilesRe(
            Compiler.filterFiles(
                Compiler.normalizeFilePaths(
                    Compiler.gatherFiles(
                        sources_dir, Settings.SOURCES_EXT
                    )
                ),
                [
                    *extraExcludes,
                    *(lambda: Settings.SOURCES_EXCLUDE_DEBUG if debug else Settings.SOURCES_EXCLUDE_PROD)()
                ]
            ),
            sources_incRe
        )
        
        # Get all hpp files and filter them
        header_files = Compiler.filterFilesRe(
            Compiler.filterFiles(
                Compiler.normalizeFilePaths(
                    Compiler.gatherFiles(
                        headers_dir, Settings.HEADERS_EXT
                    )
                ),
                [
                    *extraExcludes,
                    *(lambda: Settings.HEADERS_EXCLUDE_DEBUG if debug else Settings.HEADERS_EXCLUDE_PROD)()
                ]
            ),
            headers_incRe
        )
        # Check header files for errors
        headerErrors = Compiler.validateHeaders(header_files)
        if headerErrors[0] or headerErrors[1]:
            with open(Settings.COMPILER_OUTPUT, "a") as compilerOutputFile:
                if headerErrors[0]:
                    compilerOutputFile.write(f"Naming errors:\n")
                    for i in headerErrors[0]:
                        compilerOutputFile.write(f"    - '{i}'")
                if headerErrors[1]:
                    compilerOutputFile.write(f"Pragma errors:\n")
                    for i in headerErrors[1]:
                        compilerOutputFile.write(f"    - '{i}'")
            print(colorT("Header errors found (Dumped into compilerLog)", Colors.RED))
            return False
        
        # Determine which files need to be compiled
        to_compile = source_files if makeAll else cache.getChangedSourcesAndUpdate(source_files, header_files, comp_args_hash)
        
        #? Shared variables
        compiled_out_dir = os.path.join(cache_dir, 'compiled')
        
        #? Compilation and linking
        with open(Settings.COMPILER_OUTPUT, "ab") as compilerOutputFile:
            compilerOutputFile.truncate(0) # Empty file for this compiler iteration
            
            #* Compiler
            if to_compile:
                print(colorT("Compiling...", Colors.BLUE))
                compiled_all_success = Compiler._compile(compilerOutputFile, cache, debug, compiled_out_dir, to_compile, header_files, comp_args)
            
                #? Dump cache      
                with open(cache_file, 'w') as cacheFile:
                    cacheFile.write(cache.dumps())
            
                if not compiled_all_success and not forceLink:
                    print(colorT("Compilation finished with errors", Colors.RED))
                    return False
                print(colorT("Compilation finished successfully", Colors.GREEN))
            else:
                print(colorT("Using cached object files...", Colors.GREEN))

            #* Linker
            if cache.needsNewLinking(source_files, outputFile) or makeAll:
                print(colorT("Linking...", Colors.BLUE))
                linked_all_success = Compiler._link(compilerOutputFile, debug, source_files, compiled_out_dir, outputFile, extraFlags)
                
                if not linked_all_success:
                    print(colorT("Linking finished with errors", Colors.RED))
                    return False
                print(colorT("Linking finished successfully", Colors.GREEN))
                
                cache.commitPendingLinkage(outputFile)
                #? Dump cache      
                with open(cache_file, 'w') as cacheFile:
                    cacheFile.write(cache.dumps())
            
            return True

    @staticmethod
    def _compile(
        logFile          : IO[bytes],
        cache            : CompileCache, 
        debug            : bool,
        compiled_out_dir : str,
        to_compile       : List[str],
        header_files     : List[str],
        comp_args        : List[str],
    ) -> bool:
        #? Filter out duplicate header directorys
        header_dirs = set()
        for header in header_files:
            pos = header.rfind('\\')
            if pos == -1:
                pos = header.rfind('/')
                if pos == -1:
                    raise ValueError("HeaderFile is not in a subdirectory")
            
            header_dirs.add(header[:pos+1])
        
        #? Add header directorys to comp_args
        for header_dir in header_dirs:
            comp_args.append(f'-I{os.path.realpath(header_dir)}')
        
        #? Compile sourcefiles
        compiled_all_success = True
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
                    ),
                    *Settings.COMP_LAST_FLAGS
                ],
                stdout=subprocess.PIPE,
                stderr=subprocess.STDOUT
            )
            logFile.write(proc.stdout)
            
            if proc.returncode != 0:
                compiled_all_success = False
                cache.removeFileFromCache(source_file)
        
        return compiled_all_success
    
    @staticmethod
    def _link(
        logFile          : IO[bytes],
        debug            : bool,
        source_files     : List[str],
        compiled_out_dir : str,
        outputFile       : str,
        extraFlags       : List[str],
    ) -> bool:
        #? Translate all sourceFilesPaths to objectFilePaths
        object_files = [
            os.path.realpath(
                os.path.join(
                    compiled_out_dir,
                    os.path.splitext(source_file)[0] + ".o"
                )
            ) for source_file in source_files
        ]
        
        #Make sure output directory exists
        Path(os.path.join(os.path.dirname(os.path.realpath(outputFile)))).mkdir(parents=True, exist_ok=True)
        
        proc = subprocess.run(
            [
                'g++',
                *extraFlags,
                *Settings.LINK_SHARED_FLAGS,
                *(lambda: Settings.LINK_DEBUG_FALGS if debug else Settings.LINK_PROD_FLAGS)(),
                '-o',
                os.path.realpath(outputFile),
                *object_files,
                *Settings.LINK_LAST_FLAGS,
            ],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT
        )
        logFile.write(proc.stdout)
        
        return proc.returncode == 0
