/**
 * @file imageinspectionwidget.h
 *
 * @brief contains class ImageInspectionWidget
 */
#ifndef IMAGEINSPECTIONWIDGET_H
#define IMAGEINSPECTIONWIDGET_H

#include <imagegallery.h>
#include <imagegallerytree.h>
#include <QKeyEvent>
#include <QWidget>

namespace Ui {
class ImageInspectionWidget;
}
/**
 * @brief The ImageInspectionWidget class is UI class which can display pictures from directory structures
 */
class ImageInspectionWidget : public QWidget {
Q_OBJECT

protected:

    /**
     * @brief changeEvent event handler
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

    /**
     * @brief keyPressEvent is used for handling keypress
     *
     * @param event key press
     */
    void keyPressEvent(QKeyEvent *event) override;


public:
    /**
     * @brief ImageInspectionWidget creates a new ImageInspectionWidget
     * @param parent optional parent argument
     */
    explicit ImageInspectionWidget(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~ImageInspectionWidget() override;

    /**
     * @brief ImageInspectionWidget creates a new ImageInspectionWidget
     * @param parent optional parent argument
     * @param inputPath absolute path to images
     * @param trainingPath absolute path to images
     */
    ImageInspectionWidget(QWidget *parent, const QStringList &inputPath, const QStringList &trainingPath);

    /**
     * @brief setCurrentDataSetTrainImages updates display of current training dataset images
     * @param labelToPathsMap current training dataset
     */
    void setCurrentDataSetTrainImages(const QMap<QString, QStringList> &labelToPathsMap);

    /**
     * @brief setCurrentDataSetValidationImages updates display of current validation dataset images
     * @param labelToPathsMap current validation dataset
     */
    void setCurrentDataSetValidationImages(const QMap<QString, QStringList> &labelToPathsMap);

    /**
     * @brief setNewValidationImages updates display of new validation images
     * @param labelToPathsMap new validation dataset
     */
    void setNewValidationImages(const QMap<QString, QStringList> &labelToPathsMap);

    /**
     * @brief setNewTrainImages updates display of new training images
     * @param labelToPathsMap new training dataset
     */
    void setNewTrainImages(const QMap<QString, QStringList> &labelToPathsMap);

public slots:

    /**
     * @brief slot_imagesUpdated is used when display updates are completed
     */
    void slot_imagesUpdated();

    /**
     * @brief slot_startLoading is used when display updates are started
     */
    void slot_startLoading();

signals:

    /**
     * @brief sig_mergeDatasets signals request to merge new images with existing dataset
     */
    void sig_mergeDatasets();

    /**
     * @brief sig_removeImages signals removal of images from dataset/temp images
     * @param treeWidgetIndex index of dataset (temp/dataset + training/validation)
     * @param removedImages map of images to remove
     */
    void sig_removeImages(int treeWidgetIndex, QMap<QString, QList<int>> removedImages);


private slots:

    [[maybe_unused]] void on_pushButton_commit_clicked();

    [[maybe_unused]] void on_pushButton_removeImages_clicked();

private:
    Ui::ImageInspectionWidget *ui;



};

#endif // IMAGEINSPECTIONWIDGET_H
