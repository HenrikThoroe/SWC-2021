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