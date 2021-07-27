#ifndef IMAGESECTION_H
#define IMAGESECTION_H

#include "imagegallery.h"
#include "imagegallerytree.h"
#include <QWidget>

namespace Ui {
class imagesection;
}
/**
 * @brief The ImageSection class is UI class which can display pictures from directory structures
 */
class ImageSection : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief ImageSection creates a new ImageSection
     * @param parent optional parent argument
     */
    explicit ImageSection(QWidget *parent = nullptr);
    ~ImageSection();

    /**
     * @brief ImageSection creates a new ImageSection
     * @param parent optional parent argument
     * @param inputPath absolute path to images
     * @param trainingPath absolute path to images
     */
    ImageSection(QWidget *parent, QStringList inputPath, QStringList trainingPath);
    void setCurrentDataSetTrainImages(QMap<QString, QStringList> labelToPathsMap);
    void setCurrentDataSetValidationImages(QMap<QString, QStringList> labelToPathsMap);

    void setNewValidationImages(QMap<QString, QStringList> labelToPathsMap);
    void setNewTrainImages(QMap<QString, QStringList> labelToPathsMap);

private:
    void replaceGalleryTree(ImageGalleryTree* oldGalleryTree, ImageGalleryTree* newGalleryTree);

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
    Ui::imagesection *ui;



};

#endif // IMAGESECTION_H
