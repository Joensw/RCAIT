#ifndef IMAGEGALLERY_H
#define IMAGEGALLERY_H


#include <QListWidget>
#include <QDir>
#include <QThread>
#include <view/utilities/aspectratiolabel.h>

/**
 * @brief The ImageGallery class shows a list of images.
 *
 */
class ImageGallery : public QListWidget
{
    Q_OBJECT

public:

    /**
     * @brief ImageGallery constructs a new ImageGallery.
     *
     * @param parent optional parent widget
     */
    explicit ImageGallery(QWidget *parent = nullptr);

    ~ImageGallery();


    /**
     * @brief removeselected removes all selected images from the gallery.
     *
     */
    QList<int> removeselected();

    /**
     * @brief addImages adds images from paths to gallery.
     *
     * @param pathList list of image paths
     */
    void addImages(const QStringList& pathList);

    /**
     * @brief addImages adds images from an imagelist to gallery.
     *
     * @param imageList list of images
     */
    void addImages(QList<QImage> imageList);

    /**
     * @brief concurrentAddImages adds images of directory concurrently.
     *
     * @param path directory path
     */
    void concurrentAddImages(const QString& path);

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
    void concurrentAddImages(const QStringList &pathList);

    /**
     * @brief addImage adds an image to gallery.
     *
     * @param image image to add
     */
    void addImage(const QImage& image);

    /**
     * @brief setDragDropEnabled enables/disables drag&drop in the gallery.
     *
     * @param var true or false
     */
    void setDragDropEnabled(bool var);

    /**
     * @brief minimumSizeHint gets minimum size of gallery.
     *
     * @return size hint
     */
    QSize minimumSizeHint() const override;

    /**
     * @brief sizeHint gets preferred size of gallery.
     *
     * @return size hint
     */
    QSize sizeHint() const override;

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

    // used for adding images concurrently, safely stoppable
    class addImagesTask : public QThread {
    public:
        addImagesTask(ImageGallery *gallery, QStringList imageList) {
            abort = false;
            this->mGallery = gallery;
            this->mImageList = std::move(imageList);
        }

        void run() override {
                 foreach(QString imageName, mImageList) {
                    if (abort) return;;
                    mGallery->addImage(QImage(imageName));
                }
        }

        void quit() {
            abort = true;
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
    int mRows = - 1;

};

#endif // IMAGEGALLERY_H