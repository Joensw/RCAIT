#ifndef RCAIT_IMAGECONTROLLER_H
#define RCAIT_IMAGECONTROLLER_H


#include <Qt>
#include "imageloader.h"
#include "imageinspectionwidget.h"
#include "importfileswidget.h"
#include "datamanager.h"
#include "imagesection.h"

class ImageController {
public:
    ImageController(ImageSection* imageSection, ImportFilesWidget* importFilesWidget, DataManager* dataManager);

private:
    ImageLoader m_imageLoader;

public slots:
    void slot_remove(int sectionIndex, int imgIndex);
    void slot_loadInputImages(QString pluginName, int count, QStringList labels, int split);
    void slot_confirm();
    void slot_imagesReady();
    //Todo connect
};


#endif //RCAIT_IMAGECONTROLLER_H
