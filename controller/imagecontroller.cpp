//
// TODO: Replace this dummy with code
//

#include "imagecontroller.h"

ImageController::ImageController(ImageSection *imageSection, ImportFilesWidget *importFilesWidget,
                                 DataManager *dataManager) {

m_dataManager = dataManager;
m_imageSection = imageSection;
m_importFilesWidget = importFilesWidget;

importFilesWidget->setAvailablePlugins(dataManager->getImageLoaderPluginNames());
m_importFilesWidget = importFilesWidget;

connect(m_importFilesWidget, &ImportFilesWidget::sig_loadInputImages, this, &ImageController::slot_loadInputImages);


}

void ImageController::slot_remove(int sectionIndex, int imgIndex) {

}

void ImageController::slot_loadInputImages(QString pluginName, int count, QStringList labels, int split) {
    m_importFilesWidget->updateProgressBar(0);
    qDebug() << "slot_inputimages called";

    qDebug() << pluginName;
    qDebug() << count;
    qDebug() << labels;
    qDebug() << split;


    QString tempDir = m_dataManager->getProjectTempDir();
    qDebug() << tempDir;
    m_imageLoader = new ImageLoader();
    m_imageLoader->loadInputImages(count,labels,pluginName,tempDir);
    connect(m_imageLoader, &ImageLoader::sig_progress, this, &ImageController::slot_handelImageLoadProgress);
    m_imageLoader->load();

}

void ImageController::slot_confirm() {

}

void ImageController::slot_imagesReady() {

}

void ImageController::slot_handelImageLoadProgress(int progress)
{
    m_importFilesWidget->updateProgressBar(progress);
}

void ImageController::slot_openProject()
{
    qDebug() << "Project chosen";
}
