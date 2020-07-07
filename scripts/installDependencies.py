from sys import platform as P
import subprocess
import os
import json

from helpers.colorit import color, colors


print(color("Trying to install dependencies", colors.PURPLE))

#* Setup environment
FNULL = open(os.devnull, 'w')
currentDirectory = os.path.realpath('.')

if P == "linux" or P == "linux2" or P == "darwin":
    platform = "unix"
elif P == "win32":
    platform = "win"
    input(f"Press {color('enter', colors.ORANGE)} if you use {color('PowerShell', colors.ORANGE)}, {color('otherwise exit', colors.ORANGE)} and change it")
else:
    raise EnvironmentError(f"Platform {platform} not supported")

python = input(f"Please input your {color('Python3 callName', colors.ORANGE)} (what you use to start python): ")

#*Create Venv
print(f"{color('Creating', colors.BLUE)} Venv...")
subprocess.run([python, "-m", "venv", "venv"], stdout=FNULL, stderr=subprocess.STDOUT)

#*Install dependencies
print(f"{color('Installing', colors.BLUE)} dependencies...")
if platform == "linux":
    subprocess.run([
        "bash", f"{currentDirectory}/venv/Scripts/activate", "&&",
        "pip", "install", "-r", "requirements.txt"
        ], shell=True, stdout=FNULL, stderr=subprocess.STDOUT)
else:
    subprocess.run([
        "powershell.exe", f"{currentDirectory}\\venv\\Scripts\\Activate.ps1", ";",
        "pip", "install", "-r", "requirements.txt"
        ], shell=True, stdout=FNULL, stderr=subprocess.STDOUT)

#*Save config
with open(os.path.join(currentDirectory, "helpers/config.json"), "w") as file:
    json.dump({"istalled": True, "platform": platform}, file)


print(color("All set, you can now use all other scripts", colors.GREEN))