# Install latest packages
sudo apt update
sudo apt upgrade

# Install build dependencies: gcc, python, pip, boost
sudo apt install -y build-essential
sudo apt install -y python3
sudo apt install -y python3-pip
sudo apt install -y libboost-all-dev

# Install build-tools 
cd ./PyBlokusTools
sudo python3 -m pip install --upgrade .
cd ../
