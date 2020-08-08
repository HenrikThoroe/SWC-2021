from typing import List

import os

class Settings():
    WORK_DIRECTORY  = '.pybt-cache'
    COMPILER_OUTPUT = 'compilerOutput.txt'
    CACHE_FILE      = 'compilecache.json'
    
    SOURCES_DIR = 'app/src'
    HEADERS_DIR = 'app/include'
    
    SOURCES_EXT = '.cpp'
    HEADERS_EXT = '.hpp'
    
    SOURCES_EXCLUDE_PROD  = []
    SOURCES_EXCLUDE_DEBUG = []
    
    HEADERS_EXCLUDE_PROD  = []
    HEADERS_EXCLUDE_DEBUG = []
    
    COMP_SHARED_FLAGS = ['-c', '-std=c++17', '-m64']
    COMP_PROD_FLAGS   = ['-Ofast', '-flto', '-mpopcnt', '-fwhole-program', '-march=broadwell', '-static']
    COMP_DEBUG_FALGS  = ['-g3', '-fsanitize=address', '-fsanitize-address-use-after-scope', '-Wall']

    LINK_SHARED_FLAGS = []
    LINK_PROD_FLAGS   = []
    LINK_DEBUG_FALGS  = []
    
    @staticmethod
    def compileSettings() -> None:
        """Make settings usable
        """
        def normalizePaths(paths: List[str]) -> List[str]:
            """Normalize all paths

            Arguments:
                paths {List[str]} -- Non normalized paths in unix representation

            Returns:
                List[str] -- Normalized paths
            """
            return [os.path.normpath(os.path.normcase(path)) for path in paths]
        
        Settings.SOURCES_DIR = normalizePaths(Settings.SOURCES_DIR)
        Settings.HEADERS_DIR = normalizePaths(Settings.HEADERS_DIR)
        
        Settings.SOURCES_EXCLUDE_PROD  = normalizePaths(Settings.SOURCES_EXCLUDE_PROD)
        Settings.SOURCES_EXCLUDE_DEBUG = normalizePaths(Settings.SOURCES_EXCLUDE_DEBUG)
        
        Settings.HEADERS_EXCLUDE_PROD  = normalizePaths(Settings.HEADERS_EXCLUDE_PROD)
        Settings.HEADERS_EXCLUDE_DEBUG = normalizePaths(Settings.HEADERS_EXCLUDE_DEBUG)
