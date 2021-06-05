#!/bin/bash -ue
python3 manage.py migrate --noinput
python3 manage.py init_rabbit 
