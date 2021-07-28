from django.shortcuts import render

# Create your views here.
def index(request):
    return render(request, 'dj/index.html')


def request_page(request):
    if(request.GET.get('mybtn')):
        (int(request.GET.get('mytextbox')))
    
    return render(request,'dj/index.html')
