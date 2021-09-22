#Installation
#pip install simple_image_download 
#or get it from https://github.com/RiddlerQ/simple_image_download

from argparse import ArgumentParser
from simple_image_download import simple_image_download as simp
#https://github.com/gurugaurav/bing_image_downloader

progress = 0

parser = ArgumentParser()
parser.add_argument("-p", "--path", dest="path",
                    help="write images to PATH", metavar="PATH")
parser.add_argument("-c", "--count", dest="imagecount", metavar="COUNT", type=int,
                    help="number of images to download per label")
parser.add_argument("-l", "--labels", nargs="+",
                    help="labels for images") 


args = parser.parse_args()
args_dict = vars(args)

print(int(progress), flush= True)


numLabels = len(args_dict['labels'])
labelProgress = 100/numLabels


response = simp.simple_image_download

response().download('bear', 500)

print(response().urls('bear', 5))



for label in args_dict['labels']:
    print("[%] Downloading Images for label " + label, flush= True)
    downloader.download(label, limit=args_dict['imagecount'],  output_dir=args_dict['path'], adult_filter_off=True, force_replace=False, timeout=60, verbose=True)
    
    progress+= labelProgress
    print(int(progress), flush=True)


print("[%] Downloading Images successful", flush=True)

