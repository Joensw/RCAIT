/**
 * @file imageloaderplugin.h
 *
 * @brief contains imageloaderplugin class
 *
 */
#ifndef IMAGELOADERPLUGIN_H
#define IMAGELOADERPLUGIN_H

#include <QString>
#include <pluginusage/progressableplugin.h>
#include "plugin.h"

/**
 * @brief The ImageLoaderPlugin class is an interface for all image loader plugins.
 *
 */
class ImageLoaderPlugin : public Plugin{

public:

    /**
     * @brief init initializes plugin.
     *
     */
    virtual void init() = 0;

    /**
     * @brief loadImages starts loading images.
     *
     * @param path directory to load images to
     * @param receiver receives progress of image loading
     * @param count number of images loaded per label
     * @param labels list of image labels
     * @return true if loading was successful, false otherwise
     */
    virtual bool loadImages(const QString &path, ProgressablePlugin* receiver, int count, const QStringList &labels) = 0;
};

QT_BEGIN_NAMESPACE

/*! The imageloaderplugin interface */
#define ImageLoaderPlugin_iid "de.Fraunhofer.IOSB.RCAIT.ImageLoaderPlugin"

Q_DECLARE_INTERFACE(ImageLoaderPlugin, ImageLoaderPlugin_iid)
QT_END_NAMESPACE

#endif //IMAGELOADERPLUGIN_H
