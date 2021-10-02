# Check imports
try:
    import flickrapi
    from argparse import ArgumentParser
    import shutil
    import requests
    from pathlib import Path
except ImportError as error:
    # Output expected ImportErrors.
    print(error.__class__.__name__ + ": " + error.msg, file=sys.stderr)
    sys.exit(1)

#C:/Python3/python.exe c:/RC/plugins/imageplugins/flickrplugin/flickrapi_photosearch.py -p C:\RC\FlickrPlugin -c 10 -l "house" "car" -k 3391c68aa039902833f0c7bb1e0755ae -s 6acffd9f01ca35c8
#Licenses: https://www.flickr.com/creativecommons/
#License Keys: https://www.flickr.com/services/api/flickr.photos.licenses.getInfo.html

url_start = 'https://live.staticflickr.com/'
file_extension = '.jpg'
progress = 0

parser = ArgumentParser()
parser.add_argument("-p", "--path", dest="path",
                    help="write images to PATH", metavar="PATH")
parser.add_argument("-c", "--count", dest="imagecount", metavar="COUNT", type=int,
                    help="number of images to download per label")
parser.add_argument("-l", "--labels", nargs='+',
                    help="labels for images in python array format") 
parser.add_argument("-k", "--key",  dest="apikey", metavar="KEY",
                    help="Flickr API Key")
parser.add_argument("-s", "--secret",  dest="apisecret", metavar="SECRET",
                    help="Flickr API Secret")                                         


args = parser.parse_args()
args_dict = vars(args)

print("Connecting to Flickr API", flush= True)
flickr = flickrapi.FlickrAPI(args_dict['apikey'], args_dict['apisecret'], format='parsed-json')
print("Connection complete", flush= True)
print(int(progress), flush= True)


numLabels = len(args_dict['labels'])
labelProgress = 100/numLabels


for label in args_dict['labels']:
    print("Requesting " + label + " fotos URLs", flush= True)
    count = args_dict['imagecount']
    currPage = 1
    jointResponses = []

    while(count>0):
        response = flickr.photos.search(text=label, per_page=args_dict['imagecount'], page=currPage, license="4,5,6,7,9,10")
        jointResponses.extend(response['photos']['photo'][:min(count,500)])
        count-=min(count,500)
        currPage+=1

    numFotos = len(jointResponses)
    if(numFotos != 0):
        fotoProgress = labelProgress/numFotos
    for foto in jointResponses:
        url = url_start
        url += foto['server']
        url += '/' 
        url += foto['id']
        url += '_' 
        url += foto['secret']
        url += file_extension
        foto['url'] = url

    print("Downloading " + label + " fotos", flush= True)
    Path(args_dict['path'] + '/' + label).mkdir(parents=True, exist_ok=True)
    for foto in jointResponses:
        r = requests.get(foto['url'], stream=True)
        with open(args_dict['path'] + '/' + label + '/' +  foto['id'] + file_extension, 'wb') as out_file:
            shutil.copyfileobj(r.raw, out_file)
        del r
        progress+=fotoProgress
        print(int(progress), flush=True)   

   
    print(int(progress), flush=True)


print("Image downloads finished successfully", flush=True)

