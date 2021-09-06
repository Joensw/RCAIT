#include "imagegallery.h"
#include "imagegallerytree.h"

#include <QDir>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QtConcurrent/QtConcurrentRun>
#include <QScroller>

ImageGalleryTree::ImageGalleryTree(QWidget* parent){
    // Add full touch compliance
    QScroller::grabGesture(this, QScroller::TouchGesture);

    setDragEnabled(false);
    setAcceptDrops(false);
    setHeaderHidden(true);

    auto root  = QTreeWidget::invisibleRootItem();
    root->setFlags(root->flags() ^Qt::ItemIsDropEnabled);

    verticalScrollBar()->grabGesture(Qt::GestureType::SwipeGesture, Qt::GestureFlag::ReceivePartialGestures);

    QFont f(font());
    f.setPointSize(10);
    setFont(f);
}


QMap<QString, QList<int>> ImageGalleryTree::removeSelected(){
    QMap<QString, QList<int>> removed;
    for(int i = 0; i < this->topLevelItemCount(); i++){
        qDebug() << this->topLevelItem(i)->text(0);
        QList<int> selectedIdx = galleries.at(i)->removeselected();
        removed.insert(this->topLevelItem(i)->text(0),selectedIdx);
    }

    return removed;
}


void ImageGalleryTree::resetTree()
{
    foreach(ImageGallery* gallery, galleries) {
        gallery->clearAndStop();
    }
    galleries.clear();
    this->clear();
}

void ImageGalleryTree::addLabel(QString label, QStringList images) {
    QTreeWidgetItem* name = new QTreeWidgetItem(this);
    name->setText(0, label);
    name->setFlags(name->flags() ^Qt::ItemIsDropEnabled);
    addTopLevelItem(name);
    QTreeWidgetItem* imageGalleryItem = new QTreeWidgetItem(name);
    ImageGallery* gallery = new ImageGallery(this);
    gallery->setDragDropEnabled(false);
    gallery->concurrentAddImages(images);
    galleries.append(gallery);
    setItemWidget(imageGalleryItem,0, gallery);
    imageGalleryItem->setFlags(Qt::ItemNeverHasChildren);

    name->addChild(imageGalleryItem);

}

void ImageGalleryTree::addLabels(QMap<QString, QStringList> labelToPathsMap) {
    foreach(QString path, labelToPathsMap.keys()){
        addLabel(path, labelToPathsMap.value(path));
    }

}
