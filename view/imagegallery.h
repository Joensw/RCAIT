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


    ImageGallery(QWidget *parent, QStringList images);

    ~ImageGallery();


    /**
     * @brief removeselected
     */
    QList<int> removeselected();

    /**
     * @brief addDir
     * @param imageDir
     *
     * Adds images in a directory to the imagelist
     */
    void addDir(const QStringList imageDir);

    void addDir(QList<QImage> imageList);

    /**
     * @brief addDir
     * @param imageDir
     *
     * Runs addDir(QDir) concurrently.
     */
    void concurrentAddDir(const QString path);

    void addImage(QImage image);

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


    void concurrentAddDir(const QStringList imageList);
private slots:
    void slot_isReady();

signals:
    void sig_stopLoading();

private:
    QThread* running;
    bool mReady = true;

};

#endif // IMAGEGALLERY_H
