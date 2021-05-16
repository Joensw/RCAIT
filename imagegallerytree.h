#ifndef IMAGEGALLERYTREE_H
#define IMAGEGALLERYTREE_H

#include "imagegallery.h"

#include <QTreeWidget>

class ImageGalleryTree : public QTreeWidget
{
public:
    ImageGalleryTree(QWidget* parent);
    ImageGalleryTree(QStringList paths);

    void addDir(QString);


    void removeSelected();
private:
    QList<ImageGallery*>* galleries = new QList<ImageGallery*>();
};

#endif // IMAGEGALLERYTREE_H
