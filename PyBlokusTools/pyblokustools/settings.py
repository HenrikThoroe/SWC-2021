from typing import Union, List, overload

import os

class Settings():
    WORK_DIRECTORY  : str = '.pybt-cache'
    COMPILER_OUTPUT : str = 'compilerOutput.txt'
    CACHE_FILE      : str = 'compilecache.json'
    
    SOURCES_DIR : str = 'app/src'
    HEADERS_DIR : str = 'app/include'
    
    SOURCES_EXT : str = '.cpp'
    HEADERS_EXT : str = '.hpp'
    
    HEADER_PRAGMA_EXCLUDEDIRS = ['app/include/libraries', 'app/tests']
    
    SOURCES_EXCLUDE_PROD  : List[str] = []
    SOURCES_EXCLUDE_DEBUG : List[str] = []
    
    HEADERS_EXCLUDE_PROD  : List[str] = []
    HEADERS_EXCLUDE_DEBUG : List[str] = []
    
    COMP_SHARED_FLAGS : List[str] = ['-c', '-std=c++17', '-m64', '-static']
    COMP_PROD_FLAGS   : List[str] = ['-Ofast', '-flto', '-mpopcnt'] #? '-march=broadwell' in real production
    COMP_DEBUG_FALGS  : List[str] = ['-g3', '-fsanitize=address', '-fsanitize-address-use-after-scope', '-Wall', '-DDEBUG']
    COMP_LAST_FLAGS   : List[str] = ['-lboost_system', '-lboost_program_options', '-lboost_thread', '-lpthread']

    LINK_SHARED_FLAGS : List[str] = [*list(filter(lambda opt: opt not in ['-c'], COMP_SHARED_FLAGS))]
    LINK_PROD_FLAGS   : List[str] = [*COMP_PROD_FLAGS, '-fuse-linker-plugin']
    LINK_DEBUG_FALGS  : List[str] = [*COMP_DEBUG_FALGS]
    LINK_LAST_FLAGS   : List[str] = ['-lpthread', '-lboost_system', '-lboost_program_options', '-lboost_thread', '-lssl', '-lcrypto', '-ldl']
    
    @staticmethod
    def compileSettings() -> None:
        """Make settings usable
        """
        @overload
        def normalizePaths(paths: str) -> str: ...
        @overload
        def normalizePaths(paths: List[str]) -> List[str]: ...
    
        def normalizePaths(paths: Union[str, List[str]]) -> Union[str, List[str]]:
            """Normalize all paths

            Arguments:
                paths {List[str]} -- Non normalized paths in unix representation

            Returns:
                List[str] -- Normalized paths
            """
            if isinstance(paths, list):   
                return [os.path.normpath(os.path.normcase(path)) for path in paths]
            elif isinstance(paths, str):
                return os.path.normpath(os.path.normcase(paths))
            else:
                raise NotImplementedError(f"Cannot normalize paths of type {type(paths)}")
        
        Settings.SOURCES_DIR = normalizePaths(Settings.SOURCES_DIR)
        Settings.HEADERS_DIR = normalizePaths(Settings.HEADERS_DIR)
        
        Settings.SOURCES_EXCLUDE_PROD  = normalizePaths(Settings.SOURCES_EXCLUDE_PROD)
        Settings.SOURCES_EXCLUDE_DEBUG = normalizePaths(Settings.SOURCES_EXCLUDE_DEBUG)
        
        Settings.HEADERS_EXCLUDE_PROD  = normalizePaths(Settings.HEADERS_EXCLUDE_PROD)
        Settings.HEADERS_EXCLUDE_DEBUG = normalizePaths(Settings.HEADERS_EXCLUDE_DEBUG)
