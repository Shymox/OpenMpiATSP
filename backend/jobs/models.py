import uuid
from django.db import models
from django.conf import settings
from django.utils import timezone

# Create your models here.
class Job(models.Model):
    
    id = models.UUIDField(primary_key=True, default=uuid.uuid4, help_text='Unique ID for this timetable task')
    title = models.CharField(max_length=120)
    input = models.CharField(max_length=32767, help_text="Traveling Salesman Problem data input")
    output = models.CharField(max_length=511, null=True, blank=True)
    publication_date = models.DateTimeField(default=timezone.now)
    computation_finish_date = models.DateTimeField(null=True, blank=True)
    
    user = models.ForeignKey(
        settings.AUTH_USER_MODEL,
        on_delete=models.CASCADE,
        related_name="jobs",
    )
    
    JOB_STATUS = (
        ('w', 'Waiting'),
        ('r', 'Running'),
        ('f', 'Finished'),
    )
    status_short = models.CharField(
        max_length=1,
        choices=JOB_STATUS,
        default='w',
        help_text='Task processing status',
    )
    
    @property
    def status(self):
        #I doubt this part is optimised...
        return dict(self.JOB_STATUS)[self.status_short]
    
    class Meta:
        ordering = ['-publication_date']
    
    def __str__(self):
        return f'[{self.user}] {self.title}'