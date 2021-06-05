#!/bin/bash -ue
./wait-for db:3306
python3 manage.py migrate --noinput
python3 manage.py init_rabbit 
python3 manage.py runserver 0.0.0.0:8000