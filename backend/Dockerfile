FROM python:3.9.2
ENV PYTHONUNBUFFERED 1

WORKDIR /backend


RUN apt-get update
RUN apt-get -y install netcat
RUN pip3 install --upgrade pip

RUN curl https://raw.githubusercontent.com/eficode/wait-for/v2.1.2/wait-for -o wait-for && chmod a+x wait-for

COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt

COPY . .
EXPOSE 8000
CMD ./init.sh
