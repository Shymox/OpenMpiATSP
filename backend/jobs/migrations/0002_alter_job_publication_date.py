# Generated by Django 3.2 on 2021-05-05 13:34

from django.db import migrations, models
import django.utils.timezone


class Migration(migrations.Migration):

    dependencies = [
        ('jobs', '0001_initial'),
    ]

    operations = [
        migrations.AlterField(
            model_name='job',
            name='publication_date',
            field=models.DateTimeField(default=django.utils.timezone.now),
        ),
    ]