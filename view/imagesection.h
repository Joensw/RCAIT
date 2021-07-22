#ifndef IMAGESECTION_H
#define IMAGESECTION_H

#include "imagegallery.h"

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



private slots:
    /**
     * @brief on_pushButton_clicked removes selected images from the display and subsequently deletes them
     */
    void on_pushButton_clicked();


private:
    Ui::imagesection *ui;



};

#endif // IMAGESECTION_H
