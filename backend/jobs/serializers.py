from rest_framework import serializers
from .models import Job

class JobSerializer(serializers.ModelSerializer):
    class Meta:
        model = Job
        fields = ('id', 'user', 'title', 'publication_date', 'status', 'computation_finish_date')
