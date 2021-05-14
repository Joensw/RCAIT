#include "imagegallery.h"
#include <QtDebug>
#include <QGridLayout>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

ImageGallery::ImageGallery(QWidget *parent) :
    QListWidget(parent)
{

    setMovement(QListView::Static);
    setViewMode(ViewMode::IconMode);
    setSelectionMode(QListView::MultiSelection);
    setIconSize(QSize(100,100));
    setFlow(QListWidget::LeftToRight);
    setResizeMode(QListWidget::Adjust);

}

ImageGallery::ImageGallery(QWidget *parent, QDir imageDirectory)
{
    setMovement(QListView::Static);
    setViewMode(ViewMode::IconMode);
    setSelectionMode(QListView::MultiSelection);
    setIconSize(QSize(100,100));
    setFlow(QListWidget::LeftToRight);
    setResizeMode(QListWidget::Adjust);
    setUniformItemSizes(true);
   ImageGallery::addDir(imageDirectory);

    //QFuture<void> future = QtConcurrent::run(&ImageGallery::addDir, imageDirectory);

}

ImageGallery::ImageGallery(QWidget *parent, QString imagePath)
{
    Q_UNUSED(parent);
    setMovement(QListView::Static);
    setViewMode(ViewMode::IconMode);
    setSelectionMode(QListView::NoSelection);
    setVisible(true);
    setLayout(new QGridLayout());

    QPixmap tempImage(imagePath);

    AspectRatioLabel *imageLabel = new AspectRatioLabel();

    imageLabel->setPixmap(tempImage);
    imageLabel->setScaledContents(true);

    layout()->addWidget(imageLabel);
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


        QImage image(path);

       int squareSize = image.height() < image.width() ? image.height() : image.width();
       int leftX = image.width()/2 - squareSize/2;
       int leftY = image.height()/2 - squareSize/2;


        QImage copy = image.copy( leftX, leftY, squareSize, squareSize);
        QListWidgetItem* item = new QListWidgetItem();
        QPixmap tempImage = QPixmap::fromImage(copy);
        item->setData(Qt::DecorationRole, tempImage.scaled(78,78,Qt::KeepAspectRatio));



        addItem(item);
    }
}
