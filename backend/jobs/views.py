from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from rest_framework import viewsets
from rest_framework import generics
from .serializers import JobListSerializer, JobCreateSerializer, JobDetailSerializer
from .models import Job
from django.contrib.auth.models import User
from rest_framework import permissions

class JobList(generics.ListCreateAPIView):
    permission_classes = [permissions.IsAuthenticated]
    
    def perform_create(self, serializer):
        serializer.save(user=self.request.user)
        #TODO add job to cluster queue
    
    #TODO perform_destroy remove job from cluster queue

    def get_queryset(self):
        return Job.objects.filter(user = self.request.user)
    
    def get_serializer_class(self):
        if self.request.method == 'GET':
            return JobListSerializer
        else:
            return JobCreateSerializer

class JobDetail(generics.RetrieveDestroyAPIView):
    permission_classes = [permissions.IsAuthenticated]
    serializer_class = JobDetailSerializer
    
    def perform_create(self, serializer):
        serializer.save(user=self.request.user)
    
    def get_queryset(self):
        return Job.objects.filter(user = self.request.user)