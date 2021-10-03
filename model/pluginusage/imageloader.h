#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QStringList>
#include <imageloaderpluginmanager.h>
#include <QtConcurrent/QtConcurrent>

/**
 * @brief The ImageLoader class used to start image loading and handle incoming results
 *
 */
class ImageLoader : public ProgressablePlugin {
    Q_OBJECT
public:

    /**
     * @brief ImageLoader constructs ImageLoader
     *
     */
    ImageLoader();

    /**
     * @brief loadInputImages starts loading of images in new thread with given arguments
     *
     * @param count number of images
     * @param labels list of labels
     * @param pluginName name of selected plugin
     * @param tempImageDir path to save images to
     */
    void loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir);

public slots:

    /**
     * @brief slot_handleClassificationResult is used to handle end of image loading
     *
     */
    void slot_handleResults();

    /**
     * @brief slot_makeProgress is called when classification made progress
     *
     * @param progress number in percent
     */
    void slot_makeProgress(int progress) override;


signals:

    /**
     * @brief sig_imagesReady signals the completion of image loading
     *
     */
    void sig_imagesReady();

private:
    ImageLoaderPluginManager& mManager = ImageLoaderPluginManager::getInstance();

};


#endif //IMAGELOADER_H
