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
connect(m_imageSection, &ImageSection::sig_mergeDatasets, this, &ImageController::slot_mergeDatasets);
connect(m_imageSection, &ImageSection::sig_removeImages, this, &ImageController::slot_remove);



}


void ImageController::slot_loadInputImages(QString pluginName, int count, QStringList labels, int split) {
    m_importFilesWidget->updateProgressBar(0);
    m_split = split;

    QString tempDir = m_dataManager->getProjectTempDir();
    m_imageLoader = new ImageLoader();
    m_imageLoader->loadInputImages(count,labels,pluginName,tempDir);
    connect(m_imageLoader, &ImageLoader::sig_progress, this, &ImageController::slot_handelImageLoadProgress);
    connect(m_imageLoader, &ImageLoader::sig_imagesReady, this, &ImageController::slot_imagesReady);
    m_imageLoader->load();

}

void ImageController::slot_confirm() {

}

void ImageController::slot_imagesReady() {

    updateNewDatasetDisplay();
    updateDatasetDisplay();
}


void ImageController::slot_handelImageLoadProgress(int progress)
{
    m_importFilesWidget->updateProgressBar(progress);
}

void ImageController::slot_openProject()
{
   updateDatasetDisplay();
   updateNewDatasetDisplay();
}

void ImageController::slot_mergeDatasets() {
    m_imageInspectionModel.mergeDataSets();
    updateNewDatasetDisplay();
    updateDatasetDisplay();

}

void ImageController::updateDatasetDisplay() {
    m_imageInspectionModel.loadDataSet(m_dataManager->getProjectDataSetDir());
    m_imageSection->setCurrentDataSetTrainImages(m_imageInspectionModel.getTrainDataset());
    m_imageSection->setCurrentDataSetValidationImages(m_imageInspectionModel.getValidationDataset());
}

void ImageController::updateNewDatasetDisplay() {
    m_imageInspectionModel.loadNewData(m_dataManager->getProjectTempDir(), m_split);
    m_imageSection->setNewTrainImages(m_imageInspectionModel.getTrainNewData());
    m_imageSection->setNewValidationImages(m_imageInspectionModel.getValidationNewData());
}

void ImageController::slot_remove(int treeWidgetIndex, QMap<QString, QList<int>> removedImages) {
    m_imageInspectionModel.removeImage(treeWidgetIndex,removedImages);
}
