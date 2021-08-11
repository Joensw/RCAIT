#ifndef IMAGECONTROLLER_H
#define IMAGECONTROLLER_H


#include <Qt>
#include "imageloader.h"
#include "importfileswidget.h"
#include "imageinspectionwidget.h"
#include "datamanager.h"
#include "imageinspectionwidget.h"
#include "imageinspectionmodel.h"

class ImageController : public QObject{
    Q_OBJECT
public:
    ImageController(ImageInspectionWidget* imageInspectionWidget, ImportFilesWidget* importFilesWidget, DataManager* dataManager);

signals:
    void sig_imagesLoaded();
private:
    ImageLoader* m_imageLoader;
    ImageInspectionWidget* m_imageinspectionwidget;
    ImportFilesWidget* m_importFilesWidget;
    DataManager* m_dataManager;
    ImageInspectionModel m_imageInspectionModel;
    int m_split = 40;
    void updateDatasetDisplay();
    void updateNewDatasetDisplay();

public slots:
    void slot_remove(int treeWidgetIndex, QMap<QString, QList<int>> removedImages);
    void slot_loadInputImages(QString pluginName, int count, QStringList labels, int split);
    void slot_confirm();
    void slot_imagesReady();
    void slot_handelImageLoadProgress(int progress);
    void slot_openProject();
    void slot_mergeDatasets();
    void slot_updateImageLoadStatusText(QString status);
    void slot_imagePluginDirectoryChanged(const QString& newDirectory);
};


#endif //IMAGECONTROLLER_H
