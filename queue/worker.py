#!/usr/bin/env python

import time
import sys
import subprocess
import random
import pika

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host='rabbit',credentials=pika.credentials.PlainCredentials("rabbitmq", "rabbitmq")))
    channel = connection.channel()

    channel.queue_declare(queue='cluster')

    def callback(ch, method, properties, body):
        print(f"[worker] received message")
        with open('buffer', 'w') as file:
            file.write(body.decode("utf-8"))
        proc = subprocess.Popen(["./cluster_mock.py", "buffer"], 
            shell=False,
            stdout=subprocess.PIPE
        )   
        out, err = proc.communicate()
        print(f"[worker] result: {out}")

        # TODO post result to the database (via REST)
        
        ch.basic_ack(method.delivery_tag)

    channel.basic_consume(queue='cluster', on_message_callback=callback)

    print(' [*] Waiting for messages. To exit press CTRL+C')
    channel.start_consuming()

if __name__ == "__main__":
    main()