# RCAIT <img alt="Logo" height="100" src="Resources/RCAIT.svg" style="float: right;" width="100"/>

Rapid Classification AI Trainer

## Welcome to RCAIT!

This is the repository for the </br>_Rapid Classification AI Trainer Project_ (PSE SS 2021) </br> developed for
_Fraunhofer IOSB_.

### Description

In order to train Deep learning based models, a lot of training data is required. Collecting and annotating this
training data can take a lot of time and resources. The goal of the **Rapid-Classification AI Trainer** PSE project is a
desktop application that uses various search terms to load images from the Internet and starts training a deep learning
model with them. Using the search terms, the images already have a class assignment and no longer need to be annotated.
A central requirement of the project is a high degree of modularity. Both the loading of the images and the AI training
are to be implemented via plug-ins, so that new data sources and new training methods can be added later.

The implementation will take place in **C⁺⁺** and **Qt**. **Git** is used for code management.

## Getting Started

![](Resources/README_Resources/tabbar.png)

The program's tab structure guides you through the process. Not all steps have to be taken. The main steps are:

* Create and/or select a project.
* Create and/or select a model.
* Download additional images with a plugin of your choice.
* Inspect the images.
* Start a training.
* Classify some images.
* Check training and classification results.

## Fullfilled Criteria

### Mandatory Criteria

- [x] Create and/or select a project.
- [x] Delete an existing project.
- [x] Add a pre-trained model.
- [x] Add a user-defined model.
- [x] Delete an existing model.
- [x] Import additional images using keywords/labels.
- [x] Load keywords/labels from the .txt file.
- [x] Load some images for training and/or validation.
- [x] Inspect the images.
- [x] Configurate and execute a data augmentation.
- [x] Start a training.
- [x] Check and save training results.
- [x] Load some images for classification.
- [x] Classify the images.
- [x] Check and save classification results.
- [x] See and analyse automatically generated:
  - Confusion matrix
  - Accuracy curve
  - Most Misclassified Images
  - Top 1 and Top 5 accuracy scores
- [x] Add new plugin(s).
- [x] Set and/or select a Classification plugin.
- [x] Set and/or select an Imageloader plugin.

### Optional Criteria

- [x] Select the interface language (English, German or Russian).
- [x] Check data augmentation preview.
- [x] Compare configuration files of two models.
- [x] Compare 2 (or more) results.
- [x] Save the vector graphics images for all results.
- [x] Support more crawler plugins for several popular search engines.
- [x] Separate validation and training data set.
- [ ] Detect objects using MMDetection.
- [ ] Log to prevent overuse of the API key.
- [ ] Integrated storage management of data sets.

## Included plugins

### Disclaimer

This program lets you download lots of images from Google, Bing and other search engines. By using it, you agree to
respect any intellectual or copyright related property rights.

Search indexes merely index images and allow you to find them. They do NOT produce their own images and, as such, they
don't own copyright on any of them. The original creators of the images own the copyrights.

**Use this program only for educational purposes.**

### Flickr Plugin

Uses the [Flickr API](https://www.flickr.com/services/api/) through the [flickrapi](https://pypi.org/project/flickrapi/)
python library. API key and secret can be obtained from Flickr by following the steps outlined in their API guide.

Can be obtained by running `pip install flickrapi`

### Bing Plugin

Download images from the Microsoft Bing search engine with
the [bing-image-downloader](https://github.com/gurugaurav/bing_image_downloader) library. Can be obtained by
running `pip install bing-image-downloader`. It is preferable to download
the [fork](https://github.com/sid7631/bing_image_downloader) which downloads less duplicates. Install
with `pip install .` in directory with setup.py.

### Folder Plugin

Load images from a specified folder into the project. Folders are specified in the settings.

### Google Plugin

Download images from the Google search engine with
the [Google-Images-Search](https://pypi.org/project/Google-Images-Search/) python library. Follow instructions there to
register a custom search engine. Runs under Linux because it's dependent on curses libary (
see [this](https://stackoverflow.com/questions/35850362/importerror-no-module-named-curses-when-trying-to-import-blessings))

### [MMClassification Plugin](https://github.com/open-mmlab/mmclassification)

MMClassification is a toolbox for image classification based on pytorch and part of the open source project [OpenMMLab](https://openmmlab.com).

#### Installation

A detailed installation guide can be found in the [documentation of MMClassification](https://mmclassification.readthedocs.io/en/latest/install.html). The application was tested with version 0.15.0 and 0.16.0. A detailed list with all requirements can be found under Documentation/requirements.txt.

* data augmentation with albumentations
  For data augmentation [albumentations](https://github.com/albumentations-team/albumentations) is needed, which can be installed with `pip install -U albumentations`.

* webp support \
  For webp images webp support must be installed with `pip install webp` and in
  the [imagenet dataset class](https://github.com/open-mmlab/mmclassification/blob/master/mmcls/datasets/imagenet.py)
  the file extension `".webp"` must be added to the allowed image extensions in `IMG_EXTENSIONS`.

#### Directory structure for config and checkpoint files

This plugin uses the existing structure of the mmclassification repository and is described in its [Tutorial](https://github.com/open-mmlab/mmclassification/blob/master/docs/tutorials/MMClassification_Tutorial.ipynb). The directory structure can be found at Documentation/MMClassificationDirectoryStructure. It contains the two folders configs and checkpoints and can be integrated into the repository or can stay seperated from it. New configs will be stored in the configs folder. In the checkpoints folder only the default checkpoint files will be stored. The user generated checkpoint files can be found in the working directory of the corresponding project directory. Due to the size of the checkpoints files, the following files have to be downloaded in the checkpoints folder. In connection with the corresponding config file we call them base models because these on ImageNet pretrained models are the starting point for the actual training process. The supported base models are: [ResNet-50](https://download.openmmlab.com/mmclassification/v0/resnet/resnet50_batch256_imagenet_20200708-cfb998bf.pth), [ResNet-101](https://download.openmmlab.com/mmclassification/v0/resnet/resnet101_batch256_imagenet_20200708-753f3608.pth), [ResNeXt-32x8d-101](https://github.com/open-mmlab/mmclassification/blob/master/configs/resnext/resnext101_32x8d_b32x8_imagenet.py), [SE-ResNet-50](https://download.openmmlab.com/mmclassification/v0/se-resnet/se-resnet50_batch256_imagenet_20200804-ae206104.pth) and [MobileNetV3 Large](https://download.openmmlab.com/mmclassification/v0/mobilenet_v3/convert/mobilenet_v3_large-3ea3c186.pth). The path to this structure must be specified in the settings of the plugin under MMClassification path.

#### Required modifications to mmcls

* Creation of the confusion matrix \
  A confusion matrix will be generated due to the specified support metric in the config file, but to save its data for
  further use the following code must be added
  to [eval_metrics.py](https://github.com/open-mmlab/mmclassification/blob/master/mmcls/core/evaluation/eval_metrics.py)
  after `confusion_matrix = calculate_confusion_matrix(pred, target)`.
    ```
    torch.set_printoptions(profile="full")    
    matrix = confusion_matrix.data.tolist()
    with open("PLACEHOLDER PATH TO MMClassification Directory/data_confusion_matrix.json", 'w') as outfile:
        json.dump(matrix, outfile)
    torch.set_printoptions(profile="default")
    ```
  The placeholder must be replaced with the path to mmclassification. The path must be same as the one specified in the
  MMClassification plugin settings under mmclassification path and the name must be data_confusion_matrix.json.

* Creation of the annotation files \
  Annotation files are needed when classifying images with the test script. Otherwise the order of the classification
  results would be unclear and so the input images would not be matched with the correct, corresponding result. This
  dataset class ensures, that the input file will be read lexicographically and that a annotation file in the input
  directory will be generated. First the following file must be added to
  the [dataset directory of mmcls](https://github.com/open-mmlab/mmclassification/tree/master/mmcls/datasets) and its
  class name must be added in the [__
  init__.py file](https://github.com/open-mmlab/mmclassification/blob/master/mmcls/datasets/__init__.py).
    ```
    import mmcv
    import numpy as np

    from .builder import DATASETS
    from .base_dataset import BaseDataset
    from.imagenet import find_folders, get_samples
    from tkinter import Tcl

    @DATASETS.register_module()
    class LexicographicallySorted(BaseDataset):
        IMG_EXTENSIONS = ('.jpg', '.jpeg', '.png', '.ppm', '.bmp', '.pgm', '.tif', '.webp')

        def load_annotations(self):
        if self.ann_file is None:
            folder_to_idx = find_folders(self.data_prefix)
            samples = get_samples(
                self.data_prefix,
                folder_to_idx,
                extensions=self.IMG_EXTENSIONS)
            if len(samples) == 0:
                raise (RuntimeError('Found 0 files in subfolders of: '
                                    f'{self.data_prefix}. '
                                    'Supported extensions are: '
                                    f'{",".join(self.IMG_EXTENSIONS)}'))

            self.folder_to_idx = folder_to_idx
        elif isinstance(self.ann_file, str):
            with open(self.ann_file) as f:
                samples = [x.strip().rsplit(' ', 1) for x in f.readlines()]
        else:
            raise TypeError('ann_file must be a str or None')

        #sort samples lexicographically
        self.samples = Tcl().call('lsort', '-dict', samples)

        data_infos = []
        path = self.data_prefix + '/val.txt'
        with open(path, 'w') as f:
            for filename, gt_label in self.samples:
                info = {'img_prefix': self.data_prefix}
                info['img_info'] = {'filename': filename}
                info['gt_label'] = np.array(gt_label, dtype=np.int64)
                data_infos.append(info)
                annotationFileLine = self.data_prefix + "/" + filename + " " + str(gt_label) + "\n"
                f.write(annotationFileLine);
        return data_infos
    ```
  The dataset can then be used in the dataset config by navigating to
  mmclassification/configs/datasets/default_dataset.py and changing the line in `test = dict(` from
  `type = dataset_type` to `type = 'LexicographicallySorted'`.

* Fix log error to allow the creation of the accuracy curve \
In the file [mmcls/apis/train.py](https://github.com/open-mmlab/mmclassification/blob/master/mmcls/apis/train.py) the priority of IterTimerHook must be [changed from 'NORMAL' to 'LOW'](https://github.com/open-mmlab/mmdetection/pull/5882/files). Otherwise the validation step will be documented incorrectly in the log.json file and the accuracy curve won't be generated.

## Remote execution

Connect to the remote server using a terminal like **MobaXTerm**. </br></br>
The program can then be started on the remote by using the command </br>`./RCAIT -platform vnc:size=1920x1080`</br>The
Qt _qVNC_ plugin then starts a VNC server on port _5900_ by default. The supplied resolution is optional, but ensures
that the window will be shown completely. Thereafter, you can view and interact with the GUI of the application from
your machine with a VNC viewer of your choosing. We recommend [TightVNC](https://www.tightvnc.com/)
or [RealVNC](https://www.realvnc.com/de/). Depending on your setup, port forwarding is also required.

You can also play around with scaling options if the **window is too small**. If the bound port is already in use, you
can **select a custom port** as well.

### Example

`QT_AUTO_SCREEN_SCALE_FACTOR=0 QT_SCALE_FACTOR=1.5 ./RCAIT -platform "vnc:size=1920x1080:port=1234"`

## Rare Cases & Fixes

### QSettings Crash

It might (very rarely but still) happen, that the QSettings Registry object is corrupted during writing/reading from the
system. If that happens, the program will not start any more and the debugger will only show `SIG_SEGFAULT at 0x0000000`
This is not a fault of our code and there is nothing we can do to fix it, because it happens before our program is even
loaded.

#### Workarounds:

- Under Linux, delete the file `/home/ies/<username>/.config/PSE2021/RCAIT.conf`
- Under Windows, delete the registry entry `Computer\HKEY_CURRENT_USER\Software\PSE_SS21\RCAIT`
- Restart the application then.

## License

RCAIT is released under the **LGPLv3** [License](LICENSE)

_( GNU LESSER GENERAL PUBLIC LICENSE_ Version 3 _)_


