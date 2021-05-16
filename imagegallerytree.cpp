#include "imagegallery.h"
#include "imagegallerytree.h"

#include <QDir>
#include <QScrollBar>
#include <QStandardItemModel>
#include <QtConcurrent/QtConcurrentRun>

QList<ImageGallery> list;

ImageGalleryTree::ImageGalleryTree(QWidget* parent){

}
ImageGalleryTree::ImageGalleryTree(QStringList paths)
{



    setDragEnabled(false);
    setAcceptDrops(true);
    setHeaderHidden(true);

     auto root  = QTreeWidget::invisibleRootItem();
     root->setFlags(root->flags() ^Qt::ItemIsDropEnabled);




    verticalScrollBar()->grabGesture(Qt::GestureType::SwipeGesture, Qt::GestureFlag::ReceivePartialGestures);







    QFont f(font());
   // f.setBold(true);
    f.setPointSize(10);
    setFont(f);


    foreach(QString path, paths){
        addDir(path);
    }
}

void ImageGalleryTree::addDir(QString path)
{
    QDir dir(path);
    QTreeWidgetItem* name = new QTreeWidgetItem(this);
    name->setText(0, dir.dirName());
    name->setFlags(name->flags() ^Qt::ItemIsDropEnabled);
    addTopLevelItem(name);




    QTreeWidgetItem* imageGalleryItem = new QTreeWidgetItem(name);
    ImageGallery* gallery = new ImageGallery(this, QDir(path));
    galleries->append(gallery);
    setItemWidget(imageGalleryItem,0, gallery);
    imageGalleryItem->setFlags(Qt::ItemNeverHasChildren);

    name->addChild(imageGalleryItem);

}

void ImageGalleryTree::removeSelected(){

    for(int i = 0; i < galleries->size(); i++){
        galleries->at(i)->removeselected();
    }
}
