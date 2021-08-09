#include "imagegallery.h"
#include <QApplication>
#include <QGridLayout>
#include <QtConcurrent/QtConcurrent>
#include <utility>
#include <QScroller>


ImageGallery::ImageGallery(QWidget *parent) :
        QListWidget(parent) {

    setMovement(QListView::Static);
    setViewMode(ViewMode::IconMode);
    setSelectionMode(QListView::MultiSelection);
    setIconSize(QSize(100, 100));
    setFlow(QListWidget::LeftToRight);
    setResizeMode(QListWidget::Adjust);
    setUniformItemSizes(true);

    setDefaultDropAction(Qt::MoveAction);
    setDragDropEnabled(false);

    // Add full touch compliance
    QScroller::grabGesture(this, QScroller::TouchGesture);

}


ImageGallery::~ImageGallery() = default;


QList<int> ImageGallery::removeselected() {
    QList<int> selected;
    for(int i = 0; i < this->count(); i++){
        if(this->item(i)->isSelected()){
            selected.append(i);
            qDebug() << item(i) << "is selected";
        }
    }
    qDeleteAll(selectedItems());
    return selected;
}

void ImageGallery::addDir(const QStringList imageDirectory)
{
            foreach(QString imageName, imageDirectory) {
                addImage(QImage(imageName));
            }
}

void ImageGallery::addDir(QList<QImage> imageList)
{
    foreach(QImage image, imageList) {
        addImage(image);
    }
}

void ImageGallery::concurrentAddDir(const QString path)
{
    class addDirTask : public QThread {
    public:
        addDirTask(ImageGallery *gallery, QDir pathDir) {
            abort = false;
            this->mGallery = gallery;
            this->mPathDir = std::move(pathDir);
        }

        ~addDirTask(){
            delete mGallery;
        }

        void run() override {
            QStringList images = mPathDir.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.png", QDir::Files);

            foreach(QString imageName, images) {
                if (abort) {
                    return;
                }
                QString localPath = mPathDir.path() + "/" + imageName;
                mGallery->addImage(QImage(localPath));
            }
        }

        void quit() {
            abort = true;
        }

    private:
        ImageGallery *mGallery;
        QDir mPathDir;
        volatile bool abort;
    };

    delete running;


    auto running = new addDirTask(this, QDir(path));

    connect(this, &ImageGallery::sig_stopLoading, running, &addDirTask::quit);
    connect(running, &QThread::finished, this, &ImageGallery::slot_isReady);

    if(count() != 0) clear();
    running->start();
    mReady = false;
}

void ImageGallery::concurrentAddDir(const QList<QImage> imageList)
{
    QtConcurrent::run(static_cast<void(ImageGallery::*)(QList<QImage>)>(&ImageGallery::addDir), this, imageList);
}

void ImageGallery::concurrentAddDir(const QList<QString> imageList)
{
    QtConcurrent::run(static_cast<void(ImageGallery::*)(QList<QString>)>(&ImageGallery::addDir), this, imageList);
}

void ImageGallery::slot_isReady()
{
    mReady = true;
}


void ImageGallery::addImage(QImage image){
    int squareSize = image.height() < image.width() ? image.height() : image.width();
    int leftX = image.width() / 2 - squareSize / 2;
    int leftY = image.height() / 2 - squareSize / 2;


    QImage copy = image.copy(leftX, leftY, squareSize, squareSize);
    QListWidgetItem *item = new QListWidgetItem();
    QPixmap tempImage = QPixmap::fromImage(copy);
    item->setData(Qt::DecorationRole, tempImage.scaled(200, 200, Qt::KeepAspectRatio));


    addItem(item);
}

void ImageGallery::setDragDropEnabled(bool var)
{
    setDragEnabled(var);
    setAcceptDrops(var);
}

QSize ImageGallery::minimumSizeHint() const
{
    QSize size(parentWidget()->size());
    size.setHeight(size.height() - 60);
    return size;
}

QSize ImageGallery::sizeHint() const
{
    return minimumSizeHint();
}

void ImageGallery::clearAndStop()
{
    emit sig_stopLoading();
    while(!mReady){
        QApplication::processEvents();
        QThread::sleep(1);
    };
    if(count() != 0) clear();
}

ImageGallery::ImageGallery(QWidget *parent, QStringList images) {

    setMovement(QListView::Static);
    setParent(parent);
    setViewMode(ViewMode::IconMode);
    setSelectionMode(QListView::MultiSelection);
    setIconSize(QSize(100, 100));
    setFlow(QListWidget::LeftToRight);
    setResizeMode(QListWidget::Adjust);
    setUniformItemSizes(true);



    setDragEnabled(true);
    setAcceptDrops(true);
    setDefaultDropAction(Qt::MoveAction);

    QtConcurrent::run(static_cast<void(ImageGallery::*)(QList<QString>)>(&ImageGallery::addDir), this, images);

}






