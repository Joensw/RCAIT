
/**
 * @file flickrplugin.h
 *
 * @brief class definition for FlickrPlugin
 */
#ifndef FLICKRPLUGIN_H
#define FLICKRPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QSettings>
#include <QLineEdit>
#include <QProcess>
#include <QProcessEnvironment>
#include <QStringBuilder>
#include "imageloaderplugin.h"
#include "flickrsettings.h"
#include "progressableplugin.h"
#include "QRegularExpression"


/**
 * @brief The FlickrPlugin for downloading images via the Flickr API
 */
class FlickrPlugin : public QObject, ImageLoaderPlugin {
Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.FlickrPlugin" FILE "FlickrPlugin.json")
    Q_INTERFACES(ImageLoaderPlugin)

public:
    /**
     * @brief loadImages loads images through the Flickr Plugin
     * @param path to save the images to
     * @param receiver receiver takes status updates
     * @param imageCount count of images to download
     * @param label list of labels to download images of
     * @return
     */
    bool loadImages(const QString &path, ProgressablePlugin *receiver, int imageCount, const QStringList &label) override;

    /**
     * @brief getConfigurationWidget returns a widget in which the Plugin can be configured
     * @return the configuration widget of the Flickr Plugin
     */
    QSharedPointer<QWidget> getConfigurationWidget() override;

    /**
     * @brief saveConfiguration saves the configuration in the widget to the settings object
     */
    void saveConfiguration() override;

    /**
     * @brief init initializes the plugin
     */
    void init() override;

    /**
     * @brief getName returns the name of the plugin
     * @return the plugin name
     */
    QString getName() override;

private:
    FlickrSettings m_flickrSettings;
    QSharedPointer<FlickrSettings> pluginSettings;
    QScopedPointer<QProcess> m_process;
    ProgressablePlugin *m_receiver;
    // in case something goes wrong (could be read from command line)
    bool m_success = true;

    QString createCommandlineString(const QString &path, int imageCount, const QStringList &label);

private slots:

    void slot_abort();

    void slot_readOutPut();

    void slot_pluginFinished();

};
//! [0]

#endif
