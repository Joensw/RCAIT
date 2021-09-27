# RCAIT
Rapid Classification AI Trainer

## Welcome to **RCAIT**!

This is the repository for the Rapid Classification AI Trainer Project (PSE SS 2021) at Fraunhofer IOSB. It's a plugin framework for downloading images from different sources via "image loader plugins" and training and classification of models on images with
"classification plugins"

## Getting Started

The program's tab structure guides you through the process. Not all steps have to be taken. The main steps are:

*   Create and/or select a project.
*	Create and/or select a model.
*   Download additional images with a plugin of your choice.
*   Inspect the images.
*   Start a training.
*   Classify some images.
*   Check training and classification results.

## Included plugins

### Flickr Plugin

Uses the [Flickr API](https://www.flickr.com/services/api/) through the [flickrapi](https://pypi.org/project/flickrapi/) python library. Can be obtained by running pip install flickrapi. API key and secret can be obtained from Flickr by following the steps outlined in their API guide.

### Bing Plugin

Downloads images from the Microsoft Bing search engine with the [bing-image-downloader](https://github.com/gurugaurav/bing_image_downloader) library. Can be obtained by running pip install bing-image-downloader

### Folder Plugin

Loads images from a specified folder into the project. Folders are specified in the settings.

### Google Plugin

Downloads images from the Google search engine with the [Google-Images-Search](https://pypi.org/project/Google-Images-Search/) python library. Follow instructions there to register a custom search engine. Runs under Linux because it's dependent on curses libary (see [this](https://stackoverflow.com/questions/35850362/importerror-no-module-named-curses-when-trying-to-import-blessings))

### [MMClassification Plugin](https://github.com/open-mmlab/mmclassification)