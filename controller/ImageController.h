#ifndef RCAIT_IMAGECONTROLLER_H
#define RCAIT_IMAGECONTROLLER_H


#include <Qt>
#include <pluginusage/imageloader.h>
#include "ImageInspectionWidget.h"
#include "view/ImportFilesWidget.h"
#include "model/DataManager.h"

class ImageController {
public:
    ImageController(ImageInspectionWidget* imageInspectionWidget, ImportFilesWidget* importFilesWidget, DataManager* dataManager, ImageLoader loader);
public slots:
    void slot_remove(int sectionIndex, int imgIndex);
    void slot_loadInputImages(QString pluginName, int count, QStringList labels, int split);
    void slot_confirm();
    void slot_imagesReady();
    //Todo connect
};


#endif //RCAIT_IMAGECONTROLLER_H
