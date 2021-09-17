#include "imagegallery.h"
#include "imagegallerytree.h"

#include <QDir>
#include <QScrollBar>
#include <QtConcurrent/QtConcurrentRun>
#include <QScroller>
#include <mapadapt.h>

ImageGalleryTree::ImageGalleryTree(QWidget *parent) {
    // Add full touch compliance
    QScroller::grabGesture(this, QScroller::TouchGesture);

    setDragEnabled(false);
    setAcceptDrops(false);
    setHeaderHidden(true);

    auto root = QTreeWidget::invisibleRootItem();
    root->setFlags(root->flags() ^ Qt::ItemIsDropEnabled);

    verticalScrollBar()->grabGesture(Qt::GestureType::SwipeGesture, Qt::GestureFlag::ReceivePartialGestures);

    QFont f(font());
    f.setPointSize(10);
    setFont(f);
}


QMap<QString, QList<int>> ImageGalleryTree::removeSelected() {
    QMap<QString, QList<int>> removed;
    for (int i = this->topLevelItemCount() - 1; i >= 0; i--) {
        qDebug() << this->topLevelItem(i)->text(0);
        QList<int> selectedIdx = galleries.at(i)->removeselected();
        removed.insert(this->topLevelItem(i)->text(0), selectedIdx);
        if (galleries.at(i)->count() == 0) {
            qDebug() << "count 0";
            galleries.removeOne(galleries.at(i));
            delete this->takeTopLevelItem(i);
        }
    }

    return removed;
}


void ImageGalleryTree::resetTree() {
    for (ImageGallery *gallery: galleries) {
        gallery->clearAndStop();
    }
    galleries.clear();
    this->clear();
}

void ImageGalleryTree::addLabel(const QString &label, const QStringList &images) {
    if (images.empty()) return;
    auto *name = new QTreeWidgetItem(this);
    name->setText(0, label);
    name->setFlags(name->flags() ^ Qt::ItemIsDropEnabled);
    addTopLevelItem(name);
    auto *imageGalleryItem = new QTreeWidgetItem(name);
    auto *gallery = new ImageGallery(this);
    gallery->setDragDropEnabled(false);
    gallery->concurrentAddImages(images);
    galleries << gallery;
    setItemWidget(imageGalleryItem, 0, gallery);
    imageGalleryItem->setFlags(Qt::ItemNeverHasChildren);

    name->addChild(imageGalleryItem);

}

void ImageGalleryTree::addLabels(const QMap<QString, QStringList> &labelToPathsMap) {
    for (const auto &[path, images]: MapAdapt(labelToPathsMap)) {
        addLabel(path, images);
    }

}
