import sys
try:
    from argparse import ArgumentParser
    #see https://pypi.org/project/Google-Images-Search/ 
    #for instructions
    from google_images_search import GoogleImagesSearch
    import shutil
    import requests
    from pathlib import Path
except ImportError as error:
    # Output expected ImportErrors.
    print(error.__class__.__name__ + ": " + error.msg, file=sys.stderr)
    sys.exit(1)

headers = {"User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.77 Safari/537.36"}
progress = 0

parser = ArgumentParser()
parser.add_argument("-p", "--path", dest="path",
                    help="write images to PATH", metavar="PATH")
parser.add_argument("-c", "--count", dest="imagecount", metavar="COUNT", type=int,
                    help="number of images to download per label")
parser.add_argument("-l", "--labels", nargs='+',
                    help="labels for images in python array format") 
parser.add_argument("-k", "--key",  dest="apikey", metavar="KEY",
                    help="Google API Key")
parser.add_argument("-x", "--cx",  dest="cx", metavar="CX",
                    help="Google CX")                 

args = parser.parse_args()
args_dict = vars(args)

gis = GoogleImagesSearch(args_dict['apikey'], args_dict['cx'],validate_images=True)

print(int(progress), flush= True)


numLabels = len(args_dict['labels'])
labelProgress = 100/numLabels


for label in args_dict['labels']:
    print("[%] Downloading Images for label " + label, flush= True)
    _search_params = {
    'q': label,
    'num': args_dict['imagecount'],
    #'safe': 'off',
    'fileType': 'png',
    #'imgType': 'stock',
    #'imgSize': 'LARGE',
    #'imgDominantColor': 'brown',
    #'imgColorType': 'color',
    #'rights': 'cc_publicdomain'
    }

    gis.search(search_params=_search_params)#, path_to_dir=args_dict['path'] + '/' + label)
    Path(args_dict['path'] + '/' + label).mkdir(parents=True, exist_ok=True)
    fotoProgress = labelProgress/args_dict['imagecount']
    fotonumber = 0
    for image in gis.results():
        print("[%] Downloading Image " + image.url)
        r = requests.get(image.url, stream=True,headers=headers)
        with open(args_dict['path'] + '/' + label + '/' + label + '_' + str(fotonumber), 'wb') as out_file:
            shutil.copyfileobj(r.raw, out_file)
        del r
        fotonumber+=1
        print("[%] File Downloaded ! " + image.url)
        
    
    
    
    
    progress+= labelProgress
    print(int(progress), flush=True)


print("[%] Downloading Images successful", flush=True)

