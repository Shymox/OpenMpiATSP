from rest_framework import generics
from .serializers import JobListSerializer, JobCreateSerializer, JobDetailSerializer, JobResultSerializer
from .models import Job
from .permissions import IsRabbitGroup, IsRabbitGroup, IsOwnerOrAdminGroup

import os
import json
import pika

# login parameters for Rabbit Message Queue 
MQ_HOST  = os.environ["MQ_HOST"]
MQ_USER  = os.environ["MQ_USER"]
MQ_PASS  = os.environ["MQ_PASS"]
MQ_QUEUE = os.environ["MQ_QUEUE"]

class JobList(generics.ListCreateAPIView):
    permission_classes = [IsOwnerOrAdminGroup]
    
    def perform_create(self, serializer):
        obj = serializer.save(user=self.request.user)
        print("asd ", obj.id)
        #add job to cluster queue
        data = {
            "id":str(obj.id),
            "input":obj.input,
            "status":obj.status_short
        }
        json_data = json.dumps(data)

        connection = pika.BlockingConnection(pika.ConnectionParameters(host=MQ_HOST,credentials=pika.credentials.PlainCredentials(MQ_USER,MQ_PASS)))
        channel = connection.channel()
        channel.queue_declare(queue=MQ_QUEUE)
        channel.basic_publish(exchange='', routing_key=MQ_QUEUE, body=json_data)
        connection.close()

    #TODO perform_destroy remove job from cluster queue

    def get_queryset(self):
        if(self.request.user.groups.filter(name='Admin').exists()):
            return Job.objects.all()
        return Job.objects.filter(user = self.request.user)
    
    def get_serializer_class(self):
        if self.request.method == 'GET':
            return JobListSerializer
        else:
            return JobCreateSerializer

class JobDetail(generics.RetrieveDestroyAPIView):
    permission_classes = [IsOwnerOrAdminGroup]
    serializer_class = JobDetailSerializer
    
    def perform_create(self, serializer):
        serializer.save(user=self.request.user)
    
    def get_queryset(self):
        if(self.request.user.groups.filter(name='Admin').exists()):
            return Job.objects.all()
        return Job.objects.filter(user = self.request.user)

class JobResult(generics.UpdateAPIView):
    permission_classes = [IsRabbitGroup]
    serializer_class = JobResultSerializer
    queryset = Job.objects.all()