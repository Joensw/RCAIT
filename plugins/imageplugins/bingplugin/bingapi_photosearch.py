#Installation
#pip install bing-image-downloader
#or

#git clone https://github.com/gurugaurav/bing_image_downloader
#cd bing_image_downloader
#pip install .

from argparse import ArgumentParser
from bing_image_downloader import downloader
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


for label in args_dict['labels']:
    print("[%] Downloading Images for label " + label, flush= True)
    downloader.download(label, limit=args_dict['imagecount'],  output_dir=args_dict['path'], adult_filter_off=True, force_replace=False, timeout=60, verbose=True)
    
    progress+= labelProgress
    print(int(progress), flush=True)


print("[%] Downloading Images successful", flush=True)

