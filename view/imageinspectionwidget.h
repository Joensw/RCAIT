#ifndef IMAGEINSPECTIONWIDGET_H
#define IMAGEINSPECTIONWIDGET_H

#include "imagegallery.h"
#include "imagegallerytree.h"
#include <QWidget>

namespace Ui {
class ImageInspectionWidget;
}
/**
 * @brief The ImageInspectionWidget class is UI class which can display pictures from directory structures
 */
class ImageInspectionWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ImageInspectionWidget creates a new ImageInspectionWidget
     * @param parent optional parent argument
     */
    explicit ImageInspectionWidget(QWidget *parent = nullptr);
    ~ImageInspectionWidget();

    /**
     * @brief ImageInspectionWidget creates a new ImageInspectionWidget
     * @param parent optional parent argument
     * @param inputPath absolute path to images
     * @param trainingPath absolute path to images
     */
    ImageInspectionWidget(QWidget *parent, QStringList inputPath, QStringList trainingPath);
    void setCurrentDataSetTrainImages(QMap<QString, QStringList> labelToPathsMap);
    void setCurrentDataSetValidationImages(QMap<QString, QStringList> labelToPathsMap);

    void setNewValidationImages(QMap<QString, QStringList> labelToPathsMap);
    void setNewTrainImages(QMap<QString, QStringList> labelToPathsMap);

public slots:
    void slot_imagesUpdated();

    void slot_startLoading();
private:


signals:
    void sig_mergeDatasets();
    void sig_removeImages(int treeWidgetIndex, QMap<QString, QList<int>> removedImages);


private slots:
    /**
     * @brief on_pushButton_clicked removes selected images from the display and subsequently deletes them
     */
    void on_pushButton_clicked();


    void on_pushButton_commit_clicked();

    void on_pushButton_removeImages_clicked();

private:
    Ui::ImageInspectionWidget *ui;



};

#endif // IMAGEINSPECTIONWIDGET_H
