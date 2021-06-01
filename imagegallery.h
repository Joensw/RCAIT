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
    ImageGallery(QWidget *parent, const QDir& imageDirectory);
    ~ImageGallery();

    void removeselected();
    void addDir(const QDir& imageDir);
    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;


private:

};

#endif // IMAGEGALLERY_H
