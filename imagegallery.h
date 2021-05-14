#ifndef IMAGEGALLERY_H
#define IMAGEGALLERY_H


#include <QListWidget>
#include <QDir>
#include <aspectratiolabel.h>


class ImageGallery : public QListWidget
{
    Q_OBJECT

public:
    explicit ImageGallery(QWidget *parent = nullptr);
    ImageGallery(QWidget *parent, QDir imageDirectory);
    ImageGallery(QWidget *parent, QString imagePath);
    ~ImageGallery();

    void removeselected();
    void addDir(QDir imageDirectory);


private:
};

#endif // IMAGEGALLERY_H
