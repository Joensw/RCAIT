#include "imagegallery.h"
#include <QApplication>
#include <QGridLayout>
#include <QtConcurrent/QtConcurrent>
#include <utility>
#include <QScroller>
#include <QResizeEvent>


ImageGallery::ImageGallery(QWidget *parent) :
        QListWidget(parent) {

    setMovement(QListView::Static);
    setViewMode(ViewMode::IconMode);
    setSelectionMode(QListView::MultiSelection);
    setFlow(QListWidget::LeftToRight);
    setResizeMode(QListWidget::Adjust);
    setUniformItemSizes(true);
    setIconSize(QSize(200,200));
    setDefaultDropAction(Qt::MoveAction);
    setDragDropEnabled(false);

    // Add full touch compliance
    QScroller::grabGesture(this, QScroller::TouchGesture);

}


ImageGallery::~ImageGallery() = default;


QList<int> ImageGallery::removeselected() {
    QList<int> selected;
    for (int i = 0; i < this->count(); i++) {
        if (this->item(i)->isSelected()) {
            selected.append(i);
            qDebug() << item(i) << "is selected";
        }
    }
    qDeleteAll(selectedItems());
    return selected;
}

void ImageGallery::addImages(const QStringList &imageDirectory) {
    for (const QString &imageName: imageDirectory) addImage(QImage(imageName));
}

void ImageGallery::addImages(const QList<QImage> &imageList) {
    for (const QImage &image: imageList) addImage(image);
}

void ImageGallery::concurrentAddImages(const QString &path) {
    QStringList images;
    QDir imgDir(path);
    for (const QString &imageName:
            imgDir.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.jpeg" << "*.png", QDir::Files)) {
        images.append(imgDir.absoluteFilePath(imageName));
    }
    concurrentAddImages(images);
}

void ImageGallery::concurrentAddImages(const QList<QImage> &imageList) {
    auto task = QtConcurrent::run([this, imageList] { this->addImages(imageList); });
    Q_UNUSED(task)
}

void ImageGallery::concurrentAddImages(const QList<QString> &imageList) {
    //Auto deletes old pointer if that exists.
    running.reset(new addImagesTask(this, imageList));

    connect(this, &ImageGallery::sig_stopLoading, (addImagesTask *) &*running, &addImagesTask::quit);
    connect(&*running, &QThread::finished, this, &ImageGallery::slot_isReady);

    if (count() != 0) clear();
    running->start();
    mReady = false;
}

void ImageGallery::slot_isReady() {
    mReady = true;
}


void ImageGallery::addImage(const QImage &image) {
    int squareSize = image.height() < image.width() ? image.height() : image.width();
    int leftX = image.width() / 2 - squareSize / 2;
    int leftY = image.height() / 2 - squareSize / 2;


    QImage copy = image.copy(leftX, leftY, squareSize, squareSize);
    if (mRows >= 1) {
        mImageList.append(copy);
    }
    auto *item = new QListWidgetItem();
    QPixmap tempImage = QPixmap::fromImage(copy);
    item->setData(Qt::DecorationRole, tempImage.scaled(mImageSize, mImageSize, Qt::KeepAspectRatio));


    addItem(item);
}

void ImageGallery::setDragDropEnabled(bool var) {
    setDragEnabled(var);
    setAcceptDrops(var);
}

void ImageGallery::setImageSize(int size)
{
    mImageSize = size;
    setIconSize(QSize(mImageSize, mImageSize));
}

void ImageGallery::clearAndStop() {
    emit sig_stopLoading();
    while (!mReady) {
        QApplication::processEvents();
        QThread::sleep(1);
    }
    if (count() != 0) clear();
}

void ImageGallery::setQuadraticGrid(int rows) {
    mRows = rows;
}


void ImageGallery::resizeEvent(QResizeEvent *e) {
    if (mRows <= 0) {
        QListView::resizeEvent(e);
        return;
    }
    int squaresize = e->size().width() < e->size().height() ? e->size().width() : e->size().height();
    squaresize /= mRows;
    QSize newSize = QSize(squaresize - 1, squaresize - 1);
    setIconSize(newSize);
    for (int i = 0; i < this->count(); i++) {
        item(i)->setData(Qt::DecorationRole,
                         QPixmap::fromImage(mImageList.at(i)).scaled(squaresize, squaresize, Qt::KeepAspectRatio));
    }
    setGridSize(newSize);
    QListView::resizeEvent(e);
}






