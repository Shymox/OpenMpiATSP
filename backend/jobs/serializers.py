from rest_framework import serializers
from .models import Job
from django.contrib.auth.models import User

class JobCreateSerializer(serializers.ModelSerializer):
    class Meta:
        model = Job
        fields = ('title', 'input')

class JobListSerializer(serializers.ModelSerializer):
    class Meta:
        model = Job
        fields = ('id','title', 'status', 'publication_date', 'computation_finish_date')

class JobDetailSerializer(serializers.ModelSerializer):
    class Meta:
        model = Job
        fields = ('title', 'status', 'input', 'output', 'publication_date', 'computation_finish_date')