/**
 * @file imagecontroller.cpp
 *
 * @brief acts as controller between a classifiaction dataset and its view
 *
 * @author Sascha Rolinger
 * @author Adrian Nelson
 */
#include "imagecontroller.h"

ImageController::ImageController(ImageInspectionWidget *imageInspectionWidget, ImportFilesWidget *importFilesWidget,
                                 DataManager *dataManager)
        : m_split(40),
          m_dataManager(dataManager),
          m_imageinspectionwidget(imageInspectionWidget),
          m_importFilesWidget(importFilesWidget) {

    m_importFilesWidget->setAvailablePlugins(dataManager->getImageLoaderPluginNames());

    connect(m_importFilesWidget, &ImportFilesWidget::sig_loadInputImages, this, &ImageController::slot_loadInputImages);
    connect(m_imageinspectionwidget, &ImageInspectionWidget::sig_mergeDatasets, this,
            &ImageController::slot_mergeDatasets);
    connect(m_imageinspectionwidget, &ImageInspectionWidget::sig_removeImages, this, &ImageController::slot_remove);
    connect(m_importFilesWidget, &ImportFilesWidget::sig_abortLoading, this, &ImageController::slot_abortLoading);

}


void ImageController::slot_loadInputImages(QString pluginName, int count, QStringList labels, int split) {
    m_importFilesWidget->updateProgressBar(0);
    m_importFilesWidget->updateStatusText("");
    m_split = split;

    QString tempDir = m_dataManager->getProjectImageTempDir();
    connect(&m_imageLoader, &ImageLoader::sig_progress, this, &ImageController::slot_handleImageLoadProgress);
    connect(&m_imageLoader, &ImageLoader::sig_imagesReady, this, &ImageController::slot_imagesReady);
    connect(&m_imageLoader, &ImageLoader::sig_statusUpdate, this, &ImageController::slot_updateImageLoadStatusText);
    m_imageLoader.loadInputImages(count, std::move(labels), std::move(pluginName), tempDir);
}

void ImageController::slot_abortLoading() {
    emit m_imageLoader.sig_pluginAborted();
}

void ImageController::slot_imagesReady() {
    emit sig_startLoading();
    updateNewDatasetDisplay();
    updateDatasetDisplay();
    emit sig_imagesUpdated();
}


void ImageController::slot_handleImageLoadProgress(int progress) {
    m_importFilesWidget->updateProgressBar(progress);
}

void ImageController::slot_openProject() {
    slot_imagesReady();
}

void ImageController::slot_mergeDatasets() {
    m_imageInspectionModel.mergeDataSets(m_dataManager->getProjectDataSetTrainSubdir(),
                                         m_dataManager->getProjectDataSetValSubdir());
    slot_imagesReady();
}


void ImageController::slot_updateImageLoadStatusText(QString status) {
    m_importFilesWidget->updateStatusText(std::move(status));
}

void ImageController::slot_imagePluginDirectoryChanged(const QString &newDirectory) {
    m_importFilesWidget->setAvailablePlugins(m_dataManager->getImageLoaderPluginNames());
}

void ImageController::updateDatasetDisplay() {
    m_imageInspectionModel.loadDataSet(m_dataManager->getProjectDataSetTrainSubdir(),
                                       m_dataManager->getProjectDataSetValSubdir());
    m_imageinspectionwidget->setCurrentDataSetTrainImages(m_imageInspectionModel.getTrainDataset());
    m_imageinspectionwidget->setCurrentDataSetValidationImages(m_imageInspectionModel.getValidationDataset());
}

void ImageController::updateNewDatasetDisplay() {
    m_imageInspectionModel.loadNewData(m_dataManager->getProjectImageTempDir(), m_split);
    m_imageinspectionwidget->setNewTrainImages(m_imageInspectionModel.getTrainNewData());
    m_imageinspectionwidget->setNewValidationImages(m_imageInspectionModel.getValidationNewData());
    disconnect(&m_imageLoader, &ImageLoader::sig_imagesReady, this, &ImageController::slot_imagesReady);
}

void ImageController::slot_remove(int treeWidgetIndex, const QMap<QString, QList<int>> &removedImages) {
    m_imageInspectionModel.removeImage(treeWidgetIndex, removedImages);
}
