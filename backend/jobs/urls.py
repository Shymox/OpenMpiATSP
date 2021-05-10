from django.urls import path
from . import views

urlpatterns = [
    path('', views.jobs_list),
    path('<uuid:pk>/', views.jobs_detail),
    path('download/<uuid:pk>/', views.jobs_download),
]