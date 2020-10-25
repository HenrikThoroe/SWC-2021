FROM debian:bullseye-slim

RUN apt-get update && apt-get -y upgrade && apt-get -y install sudo
RUN useradd -m docker && echo "docker:docker" | chpasswd && adduser docker sudo

USER docker

RUN echo "docker" | sudo -S apt-get install -y libboost-all-dev
RUN echo "docker" | sudo -S apt-get install -y build-essential
RUN echo "docker" | sudo -S apt-get install -y gcc-9
RUN echo "docker" | sudo -S apt-get install -y python3
RUN echo "docker" | sudo -S apt-get install -y python3-pip

ADD . src

RUN cd src/PyBlokusTools && echo "docker" | sudo -S python3 -m pip install --upgrade .

WORKDIR /swc-2021

CMD /bin/bash