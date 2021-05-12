#!/usr/bin/env python

import time
import sys
import subprocess
import random
import pika

def main():
    connection = pika.BlockingConnection(pika.ConnectionParameters(host='localhost',credentials=pika.credentials.PlainCredentials("rabbitmq", "rabbitmq")))
    channel = connection.channel()

    channel.queue_declare(queue='cluster')


    channel.basic_publish(exchange='', routing_key='cluster', body=f"aaasd {random.randint(0,20)}")
    connection.close()
    
if __name__ == "__main__":
    main()