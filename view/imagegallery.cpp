#include "imagegallery.h"
#include <QGridLayout>
#include <QtCore>
#include <utility>





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
}


ImageGallery::ImageGallery(QWidget *parent, const QDir& imageDirectory) {
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


    class addDirTask : public QRunnable {
    public:
        addDirTask(ImageGallery *gallery, QDir path) {
            this->mGallery = gallery;
            this->mPathDir = std::move(path);
        }

        void run() override {
            mGallery->addDir(mPathDir);
        }

    private:
        ImageGallery *mGallery;
        QDir mPathDir;
    };
    auto *addDirParallel = new addDirTask(this, imageDirectory);
    QThreadPool::globalInstance()->start(addDirParallel);


}


ImageGallery::~ImageGallery() = default;


void ImageGallery::removeselected() {
    qDeleteAll(selectedItems());
}

void ImageGallery::addDir(const QDir& imageDirectory) {
    QStringList images = imageDirectory.entryList(QStringList() << "*.JPG" << "*.jpg" << "*.png", QDir::Files);


            foreach(QString imageName, images) {

            QString path = imageDirectory.path() + "/" + imageName;


            QImage image(path);

            int squareSize = image.height() < image.width() ? image.height() : image.width();
            int leftX = image.width() / 2 - squareSize / 2;
            int leftY = image.height() / 2 - squareSize / 2;


            QImage copy = image.copy(leftX, leftY, squareSize, squareSize);
            QListWidgetItem *item = new QListWidgetItem();
            QPixmap tempImage = QPixmap::fromImage(copy);
            item->setData(Qt::DecorationRole, tempImage.scaled(200, 200, Qt::KeepAspectRatio));


            addItem(item);
            }
}

void ImageGallery::concurrentAddDir(const QString path)
{
    class addDirTask : public QRunnable {
    public:
        addDirTask(ImageGallery *gallery, QDir pathDir) {
            this->mGallery = gallery;
            this->mPathDir = std::move(pathDir);
        }

        void run() override {
            mGallery->addDir(mPathDir);
        }

    private:
        ImageGallery *mGallery;
        QDir mPathDir;
    };
    auto *addDirParallel = new addDirTask(this, QDir(path));
    QThreadPool::globalInstance()->start(addDirParallel);
}

void ImageGallery::setDragDropEnabled(bool var)
{
    setDragEnabled(var);
    setAcceptDrops(var);
}

QSize ImageGallery::minimumSizeHint() const {
    QSize size(parentWidget()->size());
    size.setHeight(size.height() - 60);
    return size;
}

QSize ImageGallery::sizeHint() const {
    return minimumSizeHint();
}



