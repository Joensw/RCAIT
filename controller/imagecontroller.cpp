//
// TODO: Replace this dummy with code
//

#include "imagecontroller.h"

ImageController::ImageController(ImageSection *imageSection, ImportFilesWidget *importFilesWidget,
                                 DataManager *dataManager) {

importFilesWidget->setAvailablePlugins(dataManager->getImageLoaderPluginNames());
m_importFilesWidget = importFilesWidget;

connect(m_importFilesWidget, &ImportFilesWidget::sig_loadInputImages, this, &ImageController::slot_loadInputImages);


}

void ImageController::slot_remove(int sectionIndex, int imgIndex) {

}

void ImageController::slot_loadInputImages(QString pluginName, int count, QStringList labels, int split) {

    qDebug() << "slot_inputimages called";

    qDebug() << pluginName;
    qDebug() << count;
    qDebug() << labels;
    qDebug() << split;



    //m_imageLoader.loadInputImages(count,labels,pluginName,m_dataManger->getProjectTempDir());
    //ToDo: Mit Tempdir ersetzen wenn available
    m_imageLoader.loadInputImages(count,labels,pluginName,"C:\\Users\\Mr Stealyourgirl\\Desktop\\ok");

}

void ImageController::slot_confirm() {

}

void ImageController::slot_imagesReady() {

}
