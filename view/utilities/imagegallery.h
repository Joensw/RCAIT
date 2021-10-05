#ifndef IMAGEGALLERY_H
#define IMAGEGALLERY_H

#include <QListWidget>
#include <QDir>
#include <QThread>
#include <QImageReader>
#include <QPainter>
#include <QApplication>
#include <QGridLayout>
#include <QtConcurrent/QtConcurrent>
#include <utility>
#include <QScroller>
#include <QResizeEvent>

/**
 * @brief The ImageGallery class shows a list of images.
 */
class ImageGallery : public QListWidget {
Q_OBJECT

public:

    /**
     * @brief Constructs an ImageGallery.
     *
     * @param parent optional parent widget
     */
    explicit ImageGallery(QWidget *parent = nullptr);

    /**
     * @brief destructor of ImageGallery.
     *
     */
    ~ImageGallery() override;


    /**
     * @brief removes all selected images from the gallery.
     *
     */
    QList<int> removeselected();

    /**
     * @brief addImages adds images from paths to gallery.
     *
     * @param pathList list of image paths
     */
    void addImages(const QStringList &imageDirectory);

    /**
     * @brief addImages adds images from an imagelist to gallery.
     *
     * @param imageList list of images
     */
    void addImages(const QList<QImage> &imageList);

    /**
     * @brief concurrentAddImages adds images of directory concurrently.
     *
     * @param path directory path
     */
    void concurrentAddImages(const QString &path);

    /**
     * @brief concurrentAddImages adds images from an imagelist concurrently.
     *
     * @param imageList list of images
     */
    void concurrentAddImages(const QList<QImage> &imageList);

    /**
     * @brief addImages adds images from paths to gallery concurrently.
     *
     * @param pathList list of image paths
     */
    void concurrentAddImages(const QStringList &imageList);

    /**
     * @brief addImage adds an image to gallery.
     *
     * @param image image to add
     */
    void addImage(const QImage &image);

    /**
     * @brief setDragDropEnabled enables/disables drag&drop in the gallery.
     *
     * @param var true or false
     */
    void setDragDropEnabled(bool var);

    /**
     * @brief setImageSize sets size of images.
     *
     * @param size desired size
     */
    void setImageSize(int size);

    /**
     * @brief clearAndStop clears a gallery and stops all concurrent load tasks.
     *
     */
    void clearAndStop();

    /**
     * @brief setQuadraticGrid sets fixed number of rows and collums for gallery.
     *
     * @param rows number of rows and collums
     */
    void setQuadraticGrid(int rows);


signals:

    /**
     * @brief sig_stopLoading signals running loading tasks to stop.
     *
     */
    void sig_stopLoading();

protected slots:

    /**
     * @brief resizeEvent assures quadratic gallery on resize if quadratic grid is used, else default resize.
     *
     * @param e resize event
     */
    void resizeEvent(QResizeEvent *e);

private slots:

    void slot_isReady();


private:

    /**
     * @brief The addImagesTask class provides stoppable image addition.
     *
     */
    class addImagesTask : public QThread {
    public:

        /**
         * @brief addImagesTask accepts necessary arguments for task.
         *
         * @param gallery ImageGallery to add images
         * @param imageList list of imagepaths
         */
        addImagesTask(ImageGallery *gallery, QStringList imageList) {
            abort = false;
            this->mGallery = gallery;
            this->mImageList = std::move(imageList);
        }

        /**
         * @brief run runs task.
         *
         */
        void run() override {
            for (QString imageName: mImageList) {
                if (abort) return;

                QImage img(imageName);

                if (img.isNull()) {
                    mGallery->addImage(errorImage(imageName));

                } else {
                    mGallery->addImage(QImage(img));
                }
            }
        }

        /**
         * @brief quit stops task.
         *
         */
        void quit() {
            abort = true;
        }

        /**
        * @brief destructor for the task
        *
        */
        ~addImagesTask() override {
            quit();
            QThread::quit();
            while (!isFinished()){
                QApplication::processEvents();
                QThread::sleep(1);
            }
        }

        /**
         * @brief errorImage creates an error image to display instead of the real image
         * @param imageName name of the broken image
         * @return an image with an error message
         */
        QImage errorImage(QString &imageName) {
            //prints the error to the debug console. Will not impact performance because it's only called on error
            QImageReader reader(imageName);
            reader.read();
            qDebug() << "Error loading " << imageName << " " << reader.errorString();

            //setup the error image
            QImage naImg(":/Logos/imageerror.png");
            //change format so that we can draw on it
            QImage paintFormat = naImg.convertToFormat(QImage::Format_ARGB8565_Premultiplied);
            QString text = "Error: " + reader.errorString() + ". Image " + imageName +
                           " could not be loaded. Please check if it is valid.";
            QPainter p(&paintFormat);
            QFont font = mGallery->font();
            font.setPointSize(12);

            p.setPen(QPen(Qt::red));
            p.setFont(font);
            p.drawText(paintFormat.rect(), Qt::TextWordWrap | Qt::AlignCenter, text);

            return paintFormat;
        }

    private:
        ImageGallery *mGallery;
        QStringList mImageList;
        volatile bool abort;
    };


    QScopedPointer<QThread> running;
    bool mReady = true;

    // used for resizing images with fixed-sized lists
    QList<QImage> mImageList;
    int mRows = -1;

    int mImageSize = 200;

};

#endif // IMAGEGALLERY_H
