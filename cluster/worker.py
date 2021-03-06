#!/usr/bin/env python
import os
import json
import subprocess
import pika
import requests

# TODO: make it more secure, no hardcoded passwords!
# login parameters for Rabbit Message Queue 
MQ_HOST  = os.environ["MQ_HOST"]
MQ_USER  = os.environ["MQ_USER"]
MQ_PASS  = os.environ["MQ_PASS"]
MQ_QUEUE = os.environ["MQ_QUEUE"]

# login parameters for Django backend job status update
BCK_ADDR = os.environ["BCK_ADDR"]
BCK_USER = os.environ["BCK_USER"]
BCK_PASS = os.environ["BCK_PASS"]

bck_token = None

def bck_login():
    global bck_token
    login_dict = {
        "username": BCK_USER,
        "password": BCK_PASS
    }
    headers = {
        "Content-Type": "application/json"
    }

    x = requests.post(BCK_ADDR+"auth/login/", json = login_dict, headers = headers)
    bck_token = x.json()["token"]

def bck_logout():
    global bck_token
    headers = {
        "Authorization": f"Token {bck_token}"
    }

    x = requests.post(BCK_ADDR+"auth/logout/", headers = headers)
    bck_token = None

def bck_update(id, output=None):
    headers = {
        "Authorization": f"Token {bck_token}",
        "Content-Type": "application/json"
    }
    if (output == None):
        body = {
            "status_short": "r"
        }
    else:
        body = {
            "status_short": "f",
            "output": output
        }

    x = requests.put(BCK_ADDR+"jobs/update/"+id+"/", json = body, headers = headers)
    

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host=MQ_HOST,credentials=pika.credentials.PlainCredentials(MQ_USER, MQ_PASS)))
    channel = connection.channel()

    channel.queue_declare(queue=MQ_QUEUE)

    def callback(ch, method, properties, body):
        body_dict = json.loads(body.decode("utf-8"))
        id = body_dict['id']
        data = body_dict["input"]
        status = body_dict["status"]
        print(f"[worker] received message {id} with status {status}")

        if(status == "f"):
            print("Task already finished, ignoring!")
            ch.basic_ack(method.delivery_tag)
            return

        bck_login()
        # post 'r' job status
        bck_update(id)

        with open('buffer', 'w') as file:
            file.write(data)
        proc = subprocess.Popen(
            "mpirun --hostfile hostfile -np 4 --allow-run-as-root project buffer",
            shell=True,
            stdout=subprocess.PIPE
        )   
        out, err = proc.communicate()
        out=out.decode('UTF-8')
        print(f"[worker] result: {out}")

        # post output and 'f' status
        bck_update(id,str(out))
        bck_logout()

        ch.basic_ack(method.delivery_tag)

    channel.basic_consume(queue=MQ_QUEUE, on_message_callback=callback)

    print(' [*] Waiting for messages. To exit press CTRL+C')
    channel.start_consuming()

if __name__ == "__main__":
    main()
