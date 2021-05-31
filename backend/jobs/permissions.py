from rest_framework import permissions

class IsRabbitGroup(permissions.BasePermission):
    
    def has_object_permission(self, request, view, obj):
        return request.user and request.user.groups.filter(name='Rabbit').exists()
            
class IsOwnerOrAdminGroup(permissions.BasePermission):
    
    def has_object_permission(self, request, view, obj):
        return request.user and (
                request.user == obj.user
                or request.user.groups.filter(name='Admin').exists()
            )