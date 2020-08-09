import platform

from .coloring import Colors, colorT

def assertPlatform() -> None:
    if platform.system() != "Linux":
        print(colorT(f"{platform.system()} is not supported as a build platform", Colors.RED))
        raise SystemExit()
