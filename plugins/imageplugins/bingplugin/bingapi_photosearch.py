# Installation
# It's best to git clone https://github.com/sid7631/bing_image_downloader
# pip install . in directory with setup.py
# this fork severly reduces the amounts of duplicates


# for easy install use
# pip install bing-image-downloader
import sys
try:
    from argparse import ArgumentParser
    from bing_image_downloader import downloader
except ImportError as error:
    # Output expected ImportErrors.
    print(error.__class__.__name__ + ": " + error.msg, file=sys.stderr)
    sys.exit(1)
    
parser = ArgumentParser()
parser.add_argument("-p", "--path", dest="path",
                    help="write images to PATH", metavar="PATH")
parser.add_argument("-c", "--count", dest="imagecount", metavar="COUNT", type=int,
                    help="number of images to download per label")
parser.add_argument("-l", "--labels", nargs="+",
                    help="labels for images")

args = parser.parse_args()
args_dict = vars(args)

numLabels = len(args_dict['labels'])

for label in args_dict['labels']:
    print("[%] Downloading Images for label " + label, flush=True)
    downloader.download(label, limit=args_dict['imagecount'], output_dir=args_dict['path'], adult_filter_off=True,
                        force_replace=False, timeout=20, verbose=True)

print("[%] Downloading Images successful", flush=True)
