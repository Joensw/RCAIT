import flickrapi
from argparse import ArgumentParser
import shutil
import requests
from pathlib import Path
#C:/Python3/python.exe c:/RC/FlickrPlugin/plugin/flickrapi_test.py -p C:\RC\FlickrPlugin -c 10 -l house car -k 3391c68aa039902833f0c7bb1e0755ae -s 6acffd9f01ca35c8
#ToDo: Mit Parametern der Suchanfrage rumspielen, damit Resultate besser werden
#ToDo: Count übersetzen in page + per_page optional arguments (max per_page = 100)
url_start = 'https://live.staticflickr.com/'
file_extension = '.jpg'
progress = 0

parser = ArgumentParser()
parser.add_argument("-p", "--path", dest="path",
                    help="write images to PATH", metavar="PATH")
parser.add_argument("-c", "--count", dest="imagecount", metavar="COUNT", type=int,
                    help="number of images to download per label")
parser.add_argument("-l", "--labels", nargs="+",
                    help="labels for images") 
parser.add_argument("-k", "--key",  dest="apikey", metavar="KEY",
                    help="Flickr API Key")
parser.add_argument("-s", "--secret",  dest="apisecret", metavar="SECRET",
                    help="Flickr API Secret")                                         


args = parser.parse_args()
args_dict = vars(args)


print(args_dict['apikey'])
print(args_dict['apisecret'])
print(args_dict['path'])
print(args_dict['labels'])
print(args_dict['imagecount'])


flickr = flickrapi.FlickrAPI(args_dict['apikey'], args_dict['apisecret'], format='parsed-json')

#print progress x/100
print(int(progress), flush= True)


numLabels = len(args_dict['labels'])
labelProgress = 100/numLabels

for label in args_dict['labels']:
    response = flickr.photos.search(text=label, per_page=args_dict['imagecount'])

    numFotos = len(response['photos']['photo'])
    fotoProgress = labelProgress/numFotos
    for foto in response['photos']['photo']:
        url = url_start
        url += foto['server']
        url += '/' 
        url += foto['id']
        url += '_' 
        url += foto['secret']
        url += file_extension
        foto['url'] = url


    Path(args_dict['path'] + '/' + label).mkdir(parents=True, exist_ok=True)
    for foto in response['photos']['photo']:
        r = requests.get(foto['url'], stream=True)
        with open(args_dict['path'] + '/' + label + '/' +  foto['id'] + file_extension, 'wb') as out_file:
            shutil.copyfileobj(r.raw, out_file)
        del r
        progress+=fotoProgress
        print(int(progress), flush=True)   

   
    print(int(progress), flush=True)

#print(args)

