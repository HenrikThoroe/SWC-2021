from sys import platform as P
import subprocess
import os
import json
import importlib.util

#* Setup environment
FNULL = open(os.devnull, 'w')
currentDirectory = os.path.realpath('.')


#* Import c.color Tools
#from pyblokustools.misc.colorit import c.color, c.colors
spec = importlib.util.spec_from_file_location(
    "pyblokustools",
    os.path.join(
        currentDirectory,
        "helpers/PyblokusTools/pyblokustools/misc/colorit.py"
        )
    )
c = importlib.util.module_from_spec(spec)
spec.loader.exec_module(c)


print(c.color("Trying to install dependencies", c.colors.PURPLE))

if P == "linux" or P == "linux2" or P == "darwin":
    platform = "unix"
elif P == "win32":
    platform = "win"
    input(f"Press {c.color('enter', c.colors.ORANGE)} if you use {c.color('PowerShell', c.colors.ORANGE)}, {c.color('otherwise exit', c.colors.ORANGE)} and change it")
else:
    raise EnvironmentError(f"Platform {platform} not supported")

python = input(f"Please input your {c.color('Python3 callName', c.colors.ORANGE)} (what you use to start python): ")


#*Create Venv
print(f"{c.color('Creating', c.colors.BLUE)} Venv...")
subprocess.run([python, "-m", "venv", "venv"], stdout=FNULL, stderr=subprocess.STDOUT)


#*Install dependencies
print(f"{c.color('Installing', c.colors.BLUE)} dependencies...")
if platform == "linux":
    subprocess.run([
        "bash", os.path.join(currentDirectory, "venv/Scripts/activate"), "&&",
        "pip", "install", "-r", "requirements.txt"
        ], shell=True, stdout=FNULL, stderr=subprocess.STDOUT)
else:
    subprocess.run([
        "powershell.exe", os.path.join(currentDirectory, "venv/Scripts/Activate.ps1"), ";",
        "pip", "install", "-r", "requirements.txt"
        ], shell=True, stdout=FNULL, stderr=subprocess.STDOUT)


#*Save config
print(f"{c.color('Configuring', c.colors.BLUE)} packages...")
with open(os.path.join(currentDirectory, "helpers/PyBlokusTools/pyblokustools/data/config.json"), "w") as file:
    json.dump(
        {
            "installed": True,
            "platform": platform,
            "pyPrefix": python,
            "scriptsDir": currentDirectory
            },
        file
        )


#*Install PyblokusTools
print(f"{c.color('Installing', c.colors.BLUE)} PyBlokusTools...")
if platform == "linux":
    subprocess.run([
        "bash", os.path.join(currentDirectory, "venv/Scripts/activate"), "&&",
        "pip", "install", os.path.join(currentDirectory, "helpers/PyBlokusTools/")
        ], shell=True, stdout=FNULL, stderr=subprocess.STDOUT)
else:
    subprocess.run([
        "powershell.exe", os.path.join(currentDirectory, "venv/Scripts/Activate.ps1"), ";",
        "pip", "install", os.path.join(currentDirectory, "helpers/PyBlokusTools/")
        ], shell=True, stdout=FNULL, stderr=subprocess.STDOUT)

#*Done
print(c.color("All set, you can now use all other scripts", c.colors.GREEN))