from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
from django.views.decorators.csrf import csrf_exempt
from rest_framework.parsers import JSONParser
from rest_framework import viewsets
from .serializers import JobSerializer
from .models import Job


# Create your views here.
# class JobView(viewsets.ModelViewSet):
#     serializer_class = JobSerializer
#     queryset = Job.objects.all()


# jobs GET(
#         token
#     )
#     : jobs [
#         uuid, 
#         filename, 
#         progress(0..100),
#         status(waiting, running, finished) //, cancelled)
#     ]

# jobs POST(
#         token, 
#         file_in_csv
#     )
#     : uuid
@csrf_exempt
def jobs_list(request):
    if request.method == 'GET':
        jobs = Job.objects.all()
        serializer = JobSerializer(jobs, many=True)
        return JsonResponse(serializer.data, safe=False)

    elif request.method == 'POST':
        # TODO file parser
        data = JSONParser().parse(request)
        serializer = JobSerializer(data=data)
        if serializer.is_valid():
            #TODO check status and finish date
            serializer.save()
            return JsonResponse(serializer.data, status=201)
        return JsonResponse(serializer.errors, status=400)
        #TODO add to queueue

# jobs/<id> DELETE(
#         token
#     )
#     : response(ok, invalid)

# jobs/<id> GET
#     :    uuid, 
#         filename, 
#         progress(0..100),
#         status(waiting, running, finished) //, cancelled)
@csrf_exempt
def jobs_detail(request, pk):
    try:
        job = Job.objects.get(pk=pk)
    except Job.DoesNotExist:
        return HttpResponse(status=404)

    if request.method == 'GET':
        serializer = JobSerializer(job)
        return JsonResponse(serializer.data)

    elif request.method == 'DELETE':
        # TODO delete file
        job.delete()
        return HttpResponse(status=204)

    elif request.method == 'PUT':
        # TODO update status, change computation_finish_date 
        data = JSONParser().parse(request)
        serializer = JobSerializer(Job, data=data)
        if serializer.is_valid():
            serializer.save()
            return JsonResponse(serializer.data)
        return JsonResponse(serializer.errors, status=400)

# jobs/download/<id> GET(
#         token
#     )
#     : file_out_csv
def jobs_download(request, pk):
    try:
        job = Job.objects.get(pk=pk)
    except Job.DoesNotExist:
        return HttpResponse(status=404)
    
    return HttpResponse(status=418) # I'm a teapot Rick!