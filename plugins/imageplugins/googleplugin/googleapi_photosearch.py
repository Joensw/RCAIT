from argparse import ArgumentParser
#see https://pypi.org/project/Google-Images-Search/ 
#for instructions
from google_images_search import GoogleImagesSearch

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
    'safe': 'medium',
    'fileType': 'jpg',
    'imgType': 'photo',
    'imgSize': 'MEDIUM',
    'imgDominantColor': 'brown',
    'imgColorType': 'color',
    'rights': 'cc_sharealike'
    }

    gis.search(search_params=_search_params, path_to_dir=args_dict['path'] + '/' + label)
    
    progress+= labelProgress
    print(int(progress), flush=True)


print("[%] Downloading Images successful", flush=True)

