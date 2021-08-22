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

    enum ImageLoadType
    {
        FromDirectory  = 1,
        FromMap  = 2,
    };
    /**
     * @brief ImageGalleryTree creates a new ImageGalleryTree
     * @param parent optional parent argument
     */
    ImageGalleryTree(QWidget* parent);


    void resetTree();

    /**
     * @brief addDir add a directory to the displayed directories
     */
    void addDir(QString);

    void addLabel(QString label, QStringList images);
    void addLabels(QMap<QString, QStringList> labelToPathsMap);
    QMap<QString,QList<int>> getSelected();

    /**
     * @brief removeSelected remove images selected in the UI
     */
    QMap<QString, QList<int>> removeSelected();
    void test();
private:
    QList<ImageGallery*> galleries;

};

#endif // IMAGEGALLERYTREE_H
