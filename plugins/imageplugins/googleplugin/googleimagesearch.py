#see https://pypi.org/project/Google-Images-Search/ 
#for instructions

from google_images_search import GoogleImagesSearch

# you can provide API key and CX using arguments,
# or you can set environment variables: GCS_DEVELOPER_KEY, GCS_CX
gis = GoogleImagesSearch('AIzaSyBysnJ74tyRqSewrPdGSwcxFD_V8prjOoY', 'd07eb04ef3db44b9a',validate_images=False)

# define search params:
__search_params = {
    'q': 'car',
    'num': 123,
    'safe': 'medium',
    'fileType': 'jpg',
    'imgType': 'photo',
    'imgSize': 'MEDIUM',
    'imgDominantColor': 'brown',
    'imgColorType': 'color',
    'rights': 'cc_sharealike'
}

# this will only search for images:
#gis.search(search_params=_search_params)

# this will search and download:
gis.search(search_params=__search_params, path_to_dir='/home/sascha/scripts/dings')

# this will search, download and resize:
#gis.search(search_params=_search_params, path_to_dir='/path/', width=500, height=500)

# search first, then download and resize afterwards:
#gis.search(search_params=__search_params)
#for image in gis.results():
#    image.download('/home/sascha/scripts/')
#    image.resize(500, 500)