import uuid
from django.db import models
from django.conf import settings
from django.utils import timezone

# Create your models here.
class Job(models.Model):
    JOB_STATUS = (
        ('w', 'Waiting'),
        ('r', 'Running'),
        ('f', 'Finished'),
    )
    
    
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, help_text='Unique ID for this timetable task')
    title = models.CharField(max_length=120)
    publication_date = models.DateTimeField(default=timezone.now)
    computation_finish_date = models.DateTimeField(null=True, blank=True)
    
    user = models.ForeignKey(
        settings.AUTH_USER_MODEL,
        on_delete=models.CASCADE,
    )
    
    status = models.CharField(
        max_length=1,
        choices=JOB_STATUS,
        default='w',
        help_text='Timetable processing status',
    )
    
    class Meta:
        ordering = ['-publication_date']
    
    def __str__(self):
        return f'[{self.user}] {self.title}'