#ifndef IMAGEGALLERYTREE_H
#define IMAGEGALLERYTREE_H

#include <imagegallery.h>
#include <QTreeWidget>
#include <QDir>
#include <QScrollBar>
#include <QtConcurrent/QtConcurrentRun>
#include <QScroller>
#include <mapadapt.h>

/**
 * @brief The ImageGalleryTree class is a UI class that display a tree structure of images from directories.
 *
 */
class ImageGalleryTree : public QTreeWidget {

public:

    /**
     * @brief ImageGalleryTree creates a new ImageGalleryTree.
     *
     * @param parent optional parent argument
     */
    explicit ImageGalleryTree(QWidget *parent);

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
    /**
     * @brief shows the images under a label
     */
    void expandItem(QTreeWidgetItem *item);
    /**
     * @brief unshows the images under a label
     */
    void collapseItem(QTreeWidgetItem *item);

private:
    QList<ImageGallery*> galleries;

};

#endif // IMAGEGALLERYTREE_H
