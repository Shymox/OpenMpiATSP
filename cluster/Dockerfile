FROM python:3.9-buster
ENV PYTHONUNBUFFERED 1

WORKDIR /cluster
COPY . .

RUN apt-get update 
RUN pip install --upgrade pip
RUN pip3 install -r requirements.txt

# FROM ubuntu
ENV DEBIAN_FRONTEND="noninteractive" TZ="Europe/Warsaw"
RUN apt-get -y install cmake g++ libncurses5-dev libopenmpi-dev

RUN cmake . && make

CMD ["python", "worker.py"]
#CMD mpirun --hostfile hostfile -np 4 --allow-run-as-root project data/m6.atsp 