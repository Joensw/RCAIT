#ifndef IMAGEGALLERY_H
#define IMAGEGALLERY_H


#include <QListWidget>
#include <QDir>
#include <view/aspectratiolabel.h>


class ImageGallery : public QListWidget
{
    Q_OBJECT

public:

    /**
     * @brief ImageGallery::ImageGallery
     * @param parent
     *
     * Creates an empty ImageGallery. Use this constructor instead of ImageGallery(QWidget *parent, const QDir& imageDirectory).
     */
    explicit ImageGallery(QWidget *parent = nullptr);

    /**
     * @brief ImageGallery::ImageGallery
     * @param parent
     * @param imageDirectory
     * @deprecated please use default constructor and addDir(QDir)/concurrentAddDir(QString) instead
     */
    ImageGallery(QWidget *parent, const QDir& imageDirectory);

    ~ImageGallery();


    /**
     * @brief removeselected
     */
    void removeselected();

    /**
     * @brief addDir
     * @param imageDir
     *
     * Adds images in a directory to the imagelist
     */
    void addDir(const QDir& imageDir);

    void addDir(QList<QImage> imageList);

    /**
     * @brief addDir
     * @param imageDir
     *
     * Runs addDir(QDir) concurrently.
     */
    void concurrentAddDir(const QString path);

    /**
     * @brief setDragDropEnabled
     * @param var
     *
     */
    void setDragDropEnabled(bool var);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void clearAndStop();

    void concurrentAddDir(const QList<QImage> imageList);


signals:
    void sig_stopLoading();


private:

    void addImage(QImage image);
};

#endif // IMAGEGALLERY_H
