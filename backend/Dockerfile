FROM python:3.9.2
ENV PYTHONUNBUFFERED 1

WORKDIR /backend
COPY requirements.txt requirements.txt
RUN pip3 install -r requirements.txt

COPY . .

EXPOSE 8000
CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
