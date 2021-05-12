from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from rest_framework import viewsets
from rest_framework import generics
from .serializers import JobListSerializer, JobCreateSerializer, JobDetailSerializer, JobResultSerializer
from .models import Job
from .permissions import IsRabbitGroup, IsRabbitGroup, IsOwnerOrAdminGroup
from django.contrib.auth.models import User
from rest_framework import permissions
from django.utils import timezone

class JobList(generics.ListCreateAPIView):
    permission_classes = [IsOwnerOrAdminGroup]
    
    def perform_create(self, serializer):
        serializer.save(user=self.request.user)
        #TODO add job to cluster queue
    
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