import platform
import subprocess
import re

from .coloring import Colors, colorT

def assertPlatform() -> None:
    #? Check Linux
    if platform.system() != "Linux":
        print(colorT(f"{platform.system()} is not supported as a build platform", Colors.RED))
        raise SystemExit()
    
    #? Check ld version > 2.32
    ldVersionStr = subprocess.run(["ld", "-v"], stdout=subprocess.PIPE).stdout.decode()
    ldVersion    = float(re.findall("\d+\.\d+", ldVersionStr)[0])
    if not ldVersion > 2.32:
        print(colorT(f"ld version {ldVersion} found, 2.33+ required", Colors.RED))
        raise SystemExit()
