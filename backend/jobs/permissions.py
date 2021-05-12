from rest_framework import permissions
from django.shortcuts import get_object_or_404
from django.contrib.auth.models import User

class IsRabbitGroup(permissions.BasePermission):
    
    def has_object_permission(self, request, view, obj):
        return request.user and request.user.groups.filter(name='Rabbit').exists()
            
class IsOwnerOrAdminGroup(permissions.BasePermission):
    
    def has_object_permission(self, request, view, obj):
        return request.user and (
                request.user == obj.user
                or request.user.groups.filter(name='Admin').exists()
            )