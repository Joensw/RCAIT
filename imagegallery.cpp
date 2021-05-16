#include "imagegallery.h"
#include <QtDebug>
#include <QGridLayout>
#include <QtCore>





QString testDir = "D:/Bilder/Auto/";

//Nur für "Input Image" Tab test
ImageGallery::ImageGallery(QWidget *parent) :
    QListWidget(parent)
{

    setMovement(QListView::Static);
    setViewMode(ViewMode::IconMode);
    setSelectionMode(QListView::MultiSelection);
    setIconSize(QSize(100,100));
    setFlow(QListWidget::LeftToRight);
    setResizeMode(QListWidget::Adjust);
    setUniformItemSizes(true);




    class addDirTask : public QRunnable
    {
    public:
        addDirTask(ImageGallery* gallery, QDir path){
            this->gallery = gallery;
            this->path = path;
        }
        void run() override
        {
            gallery->addDir(path);
        }
        private: ImageGallery* gallery;
                 QDir path;
    };
    addDirTask *addDirParallel = new addDirTask(this, testDir);
    QThreadPool::globalInstance()->start(addDirParallel);

}

ImageGallery::ImageGallery(QWidget *parent, QDir imageDirectory)
{
    setMovement(QListView::Static);
    setParent(parent);
    setViewMode(ViewMode::IconMode);
    setSelectionMode(QListView::MultiSelection);
    setIconSize(QSize(100,100));
    setFlow(QListWidget::LeftToRight);
    setResizeMode(QListWidget::Adjust);
    setUniformItemSizes(true);

    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    setDragEnabled(true);
    setAcceptDrops(true);
    setDefaultDropAction(Qt::MoveAction);



    class addDirTask : public QRunnable
    {
    public:
        addDirTask(ImageGallery* gallery, QDir path){
            this->gallery = gallery;
            this->path = path;
        }
        void run() override
        {
            gallery->addDir(path);
        }
        private: ImageGallery* gallery;
                 QDir path;
    };
    addDirTask *addDirParallel = new addDirTask(this, imageDirectory);
    QThreadPool::globalInstance()->start(addDirParallel);


}


ImageGallery::~ImageGallery()
{

}



void ImageGallery::removeselected()
{
    qDeleteAll(selectedItems());
}

void ImageGallery::addDir(QDir imageDirectory)
{
    QStringList images = imageDirectory.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.png", QDir::Files);


    foreach(QString imageName, images){

        QString path = imageDirectory.path() + "/" + imageName;
        qDebug() << path;


        QImage image(path);

       int squareSize = image.height() < image.width() ? image.height() : image.width();
       int leftX = image.width()/2 - squareSize/2;
       int leftY = image.height()/2 - squareSize/2;


        QImage copy = image.copy( leftX, leftY, squareSize, squareSize);
        QListWidgetItem* item = new QListWidgetItem();
        QPixmap tempImage = QPixmap::fromImage(copy);
        item->setData(Qt::DecorationRole, tempImage.scaled(200,200,Qt::KeepAspectRatio));





        addItem(item);
    }
}

QSize ImageGallery::minimumSizeHint() const
{
    QSize size(parentWidget()->size());
    size.setHeight(size.height() - 60);
    return size ;
}

QSize ImageGallery::sizeHint() const
{
    return minimumSizeHint();
}



