import os
from django.core.management.base import BaseCommand
from django.contrib.auth.models import Group, User

BCK_USER = os.environ["BCK_USER"]
BCK_PASS = os.environ["BCK_PASS"]

class Command(BaseCommand):
    help = 'Creates read only default permission groups for users'

    def handle(self, *args, **options):
        group, created = Group.objects.get_or_create(name="Rabbit")
        user, created = User.objects.get_or_create(username=BCK_USER)
        user.set_password(BCK_PASS)
        user.save()
        user.groups.add(group)
        print(f"(re)created {BCK_USER} user and Rabbit group")
