FROM debian:bullseye-slim

RUN apt-get update && apt-get -y upgrade && apt-get -y install sudo
RUN useradd -m docker && echo "docker:docker" | chpasswd && adduser docker sudo && echo "docker" | sudo -S passwd -d docker

USER docker

RUN sudo apt-get install -y libboost-all-dev
RUN sudo apt-get install -y build-essential
RUN sudo apt-get install -y gcc-9
RUN sudo apt-get install -y python3
RUN sudo apt-get install -y python3-pip

ADD . src

RUN cd src/PyBlokusTools && sudo python3 -m pip install --upgrade .

WORKDIR /swc-2021

CMD /bin/bash