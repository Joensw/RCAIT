#ifndef IMAGESECTION_H
#define IMAGESECTION_H

#include "imagegallery.h"

#include <QWidget>

namespace Ui {
class imagesection;
}

class ImageSection : public QWidget
{
    Q_OBJECT

public:
    explicit ImageSection(QWidget *parent = nullptr);
    ~ImageSection();
    ImageSection(QWidget *parent, QString inputPath, QString trainingPath);

private slots:
    void on_pushButton_clicked();


private:
    Ui::imagesection *ui;
    ImageGallery* startGallery(QString path);


};

#endif // IMAGESECTION_H
