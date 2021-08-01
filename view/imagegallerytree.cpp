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
    ImageGallery* gallery = new ImageGallery(this);
    gallery->concurrentAddDir(path);
    galleries->append(gallery);
    setItemWidget(imageGalleryItem,0, gallery);
    imageGalleryItem->setFlags(Qt::ItemNeverHasChildren);

    name->addChild(imageGalleryItem);

}

QMap<QString, QList<int>> ImageGalleryTree::removeSelected(){

QMap<QString, QList<int>> removed;
    for(int i = 0; i < this->topLevelItemCount(); i++){
        qDebug() << this->topLevelItem(i)->text(0);
        QList<int> selectedIdx = galleries->at(i)->removeselected();
        removed.insert(this->topLevelItem(i)->text(0),selectedIdx);
    }

    return removed;
    //for(int i = 0; i < galleries->size(); i++){
        //galleries->at(i)->removeselected();
    //}
}

ImageGalleryTree::ImageGalleryTree(QMap<QString, QStringList> labelToPathsMap) {


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


      foreach(QString path, labelToPathsMap.keys()){
            addLabel(path, labelToPathsMap.value(path));
        }

}

void ImageGalleryTree::addLabel(QString label, QStringList images) {

    //QDir dir(path);
    QTreeWidgetItem* name = new QTreeWidgetItem(this);
    name->setText(0, label);
    name->setFlags(name->flags() ^Qt::ItemIsDropEnabled);
    addTopLevelItem(name);
    QTreeWidgetItem* imageGalleryItem = new QTreeWidgetItem(name);
    ImageGallery* gallery = new ImageGallery(this, images);
    galleries->append(gallery);
    setItemWidget(imageGalleryItem,0, gallery);
    imageGalleryItem->setFlags(Qt::ItemNeverHasChildren);

    name->addChild(imageGalleryItem);

}

void ImageGalleryTree::addLabels(QMap<QString, QStringList> labelToPathsMap) {
    foreach(QString path, labelToPathsMap.keys()){
        addLabel(path, labelToPathsMap.value(path));
    }

}

void ImageGalleryTree::test(){
   for(int i = 0; i < this->topLevelItemCount(); i++){
       qDebug() << this->topLevelItem(i)->text(0);
   }
}

QMap<QString, QList<int>> ImageGalleryTree::getSelected() {

    for(int i = 0; i < galleries->size(); i++){
        galleries->at(i)->removeselected();
    }

    return QMap<QString, QList<int>>();
}
