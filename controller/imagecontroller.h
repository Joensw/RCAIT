/**
 * @file imagecontroller.h
 *
 * @brief acts as controller between a classifiaction dataset and its view
 *
 * @author Sascha Rolinger
 * @author Adrian Nelson
 */

#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H

#include <Qt>
#include "imageloader.h"
#include "importfileswidget.h"
#include "imageinspectionwidget.h"
#include "datamanager.h"
#include "imageinspectionwidget.h"
#include "imageinspectionmodel.h"
#include <utility>


/**
 * @brief The ImageController class mediates between the UI of ImageInspection, ImageLoading and their logic.
 *
 */
class ImageController final : public QObject{
    Q_OBJECT
public:
    /**
     * @brief ImageController constructs an ImageController.
     *
     * @param imageInspectionWidget
     * @param importFilesWidget
     * @param dataManager
     */
    ImageController(ImageInspectionWidget* imageInspectionWidget, ImportFilesWidget* importFilesWidget, DataManager* dataManager);

    /**
     * @brief operator = deleted assignment operator
     */
    ImageController &operator=(const ImageController &) = delete;

    /**
     * @brief setSplit sets the split between validation an training images
     * @param split the split
     */
    void setSplit(int split);

public slots:

    /**
     * @brief slot_remove
     * @param treeWidgetIndex
     * @param removedImages
     */
    void slot_remove(int treeWidgetIndex, const QMap<QString, QList<int>>& removedImages);

    /**
     * @brief slot_loadInputImages starts image loading.
     *
     * @param pluginName name of image loader plugin
     * @param count number of images per label
     * @param labels list of image labels
     * @param split number of images used for validation in percent
     */
    void slot_loadInputImages(QString pluginName, int count, QStringList labels, int split);

    /**
     * @brief slot_imagesReady updates ImageInspectionWidget.
     *
     */
    void slot_imagesReady();

    /**
     * @brief slot_handleImageLoadProgress updates progressbar.
     *
     * @param progress image load progress
     */
    void slot_handleImageLoadProgress(int progress);

    /**
     * @brief slot_openProject loads ImageInspectionWidget with images of opened project.
     *
     */
    void slot_openProject();

    /**
     * @brief slot_mergeDatasets merges images of temp folder into training/validation folders.
     *
     */
    void slot_mergeDatasets();

    /**
     * @brief slot_updateImageLoadStatusText updates status message above progressbar.
     *
     * @param status status message
     */
    void slot_updateImageLoadStatusText(QString status);

    /**
     * @brief slot_imagePluginDirectoryChanged updates available image load plugins.
     *
     * @param newDirectory new image plugin directory
     */
    void slot_imagePluginDirectoryChanged(const QString& newDirectory);

    /**
     * @brief slot_abortLoading aborts image loading.
     *
     */
    void slot_abortLoading();

    /**
     * @brief slot_splitChanged used if split is changed.
     */
    void slot_splitChanged(int value);

signals:


    /**
     * @brief sig_imagesUpdated signals completion of image loading.
     */
    void sig_imagesUpdated();

    /**
     * @brief sig_startLoading signals start of image loading.
     */
    void sig_startLoading();


private:
    ImageLoader m_imageLoader;
    ImageInspectionWidget *m_imageinspectionwidget;
    ImportFilesWidget *m_importFilesWidget;
    DataManager *m_dataManager;
    ImageInspectionModel m_imageInspectionModel;
    int m_split;

    void updateDatasetDisplay();

    void updateNewDatasetDisplay();
};


#endif //IMAGECONTROLLER_H
