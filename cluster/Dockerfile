FROM python:3.9-buster
ENV PYTHONUNBUFFERED 1

WORKDIR /cluster

ENV DEBIAN_FRONTEND="noninteractive" TZ="Europe/Warsaw"
RUN apt-get update 
RUN apt-get -y install cmake g++ libncurses5-dev libopenmpi-dev netcat
RUN pip3 install --upgrade pip

RUN curl https://raw.githubusercontent.com/eficode/wait-for/v2.1.2/wait-for -o wait-for && chmod a+x wait-for

COPY requirements.txt .
RUN pip3 install -r requirements.txt

COPY . .
RUN cmake . && make

CMD ./wait-for backend:8000 && \
    ./wait-for mq:5672 && \
    python3 worker.py
#CMD mpirun --hostfile hostfile -np 4 --allow-run-as-root project data/m6.atsp 