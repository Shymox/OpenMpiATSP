FROM python:3.9.2
ENV PYTHONUNBUFFERED 1

WORKDIR /queue
COPY requirements.txt requirements.txt
RUN pip install --upgrade pip
RUN pip3 install -r requirements.txt

COPY . .

CMD ["python", "worker.py"]
