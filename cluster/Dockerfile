FROM ubuntu
ENV DEBIAN_FRONTEND="noninteractive" TZ="Europe/Warsaw"
RUN apt-get update 
RUN apt-get -y install cmake g++ libncurses5-dev libopenmpi-dev

WORKDIR /cluster
COPY . .

RUN cmake . && make

CMD mpirun --hostfile hostfile -np 4 --allow-run-as-root project data/m6.atsp 