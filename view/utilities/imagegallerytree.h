#ifndef IMAGEGALLERYTREE_H
#define IMAGEGALLERYTREE_H

#include "imagegallery.h"

#include <QTreeWidget>

/**
 * @brief The ImageGalleryTree class is a UI class that display a tree structure of images from directories.
 *
 */
class ImageGalleryTree : public QTreeWidget
{

public:

    /**
     * @brief ImageGalleryTree creates a new ImageGalleryTree.
     *
     * @param parent optional parent argument
     */
    ImageGalleryTree(QWidget* parent);

    /**
     * @brief resetTree removes all galleries and their corresponding labels from the tree.
     *
     */
    void resetTree();

    /**
     * @brief addLabel adds a label with images.
     *
     * @param label label of images
     * @param images images to add
     */
    void addLabel(const QString &label, const QStringList &images);

    /**
     * @brief addLabels adds multiple labels with images.
     *
     * @param labelToPathsMap map of labels and image path lists
     */
    void addLabels(const QMap<QString, QStringList> &labelToPathsMap);

    /**
     * @brief removeSelected remove images selected in the UI
     */
    QMap<QString, QList<int>> removeSelected();

public slots:
    void expandItem(QTreeWidgetItem *item);
    void collapseItem(QTreeWidgetItem *item);

private:
    QList<ImageGallery*> galleries;
   // bool mExpanded = false;

};

#endif // IMAGEGALLERYTREE_H
