//
// TODO: Replace this dummy with code
//

#include "imagecontroller.h"

ImageController::ImageController(ImageInspectionWidget *imageInspectionWidget, ImportFilesWidget *importFilesWidget,
                                 DataManager *dataManager, ImageLoader *loader) {

}

void ImageController::slot_remove(int sectionIndex, int imgIndex) {

}

void ImageController::slot_loadInputImages(QString pluginName, int count, QStringList labels, int split) {

    qDebug() << "slot_inputimages called\n";
    qDebug() << pluginName;
    qDebug() << count;
    qDebug() << labels;
    qDebug() << split;

}

void ImageController::slot_confirm() {

}

void ImageController::slot_imagesReady() {

}
