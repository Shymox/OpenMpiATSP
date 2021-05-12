from datetime import datetime
from rest_framework import serializers
from .models import Job
from django.contrib.auth.models import User
from django.utils import timezone

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

class JobResultSerializer(serializers.ModelSerializer):
    def update(self, instance, validated_data):
        instance.computation_finish_date = timezone.now()
        return super(JobResultSerializer,self).update(instance, validated_data)

    class Meta:
        model = Job
        fields = ('status_short', 'output', 'computation_finish_date')
        read_only_fields = ('computation_finish_date',)