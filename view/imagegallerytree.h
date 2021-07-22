#ifndef IMAGEGALLERYTREE_H
#define IMAGEGALLERYTREE_H

#include "imagegallery.h"

#include <QTreeWidget>
/**
 * @brief The ImageGalleryTree class is a UI class that display a tree structure of images from directories
 */
class ImageGalleryTree : public QTreeWidget
{
public:
    /**
     * @brief ImageGalleryTree creates a new ImageGalleryTree
     * @param parent optional parent argument
     */
    ImageGalleryTree(QWidget* parent);

    /**
     * @brief ImageGalleryTree createss a new ImageGalleryTree
     * @param paths paths of the directories to be display
     */
    ImageGalleryTree(QStringList paths);

    /**
     * @brief addDir add a directory to the displayed directories
     */
    void addDir(QString);


    /**
     * @brief removeSelected remove images selected in the UI
     */
    void removeSelected();
private:
    QList<ImageGallery*>* galleries = new QList<ImageGallery*>();
};

#endif // IMAGEGALLERYTREE_H
