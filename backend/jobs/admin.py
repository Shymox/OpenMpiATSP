from django.contrib import admin

# Register your models here.
from .models import Job

class JobAdmin(admin.ModelAdmin):
    list_display = ('id', 'user', 'title', 'publication_date', 'status', 'computation_finish_date')

# Register your models here.

admin.site.register(Job, JobAdmin)