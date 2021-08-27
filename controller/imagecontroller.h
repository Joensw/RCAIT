#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H


#include <Qt>
#include "imageloader.h"
#include "importfileswidget.h"
#include "imageinspectionwidget.h"
#include "datamanager.h"
#include "imageinspectionwidget.h"
#include "imageinspectionmodel.h"


/**
 * @brief The ImageController class mediates between the UI of ImageInspection, ImageLoading and their logic.
 *
 */
class ImageController : public QObject{
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

public slots:

    /**
     * @brief slot_remove
     * @param treeWidgetIndex
     * @param removedImages
     */
    void slot_remove(int treeWidgetIndex, QMap<QString, QList<int>> removedImages);

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
     * @brief slot_handelImageLoadProgress updates progressbar.
     *
     * @param progress image load progress
     */
    void slot_handelImageLoadProgress(int progress);

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

signals:

    /**
     * @brief sig_imagesLoaded signals completion of image loading.
     *
     */
    void sig_imagesLoaded();



    /**
     * @brief sig_imagesUpdated signals completion of image loading.
     */
    void sig_imagesUpdated();

    /**
     * @brief sig_startLoading signals start of image loading.
     */
    void sig_startLoading();


private:
    ImageLoader* m_imageLoader;
    ImageInspectionWidget* m_imageinspectionwidget;
    ImportFilesWidget* m_importFilesWidget;
    DataManager* m_dataManager;
    ImageInspectionModel m_imageInspectionModel;
    int m_split = 40;
    void updateDatasetDisplay();
    void updateNewDatasetDisplay();
};


#endif //IMAGECONTROLLER_H
