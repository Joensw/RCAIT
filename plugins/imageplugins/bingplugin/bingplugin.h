/**
 * @file bingplugin.h
 *
 * @brief contains the BingPlugin class
 */
#ifndef BINGPLUGIN_H
#define BINGPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QSettings>
#include <QLineEdit>
#include <QProcess>
#include <QStringBuilder>
#include <QProcessEnvironment>
#include "imageloaderplugin.h"
#include "bingsettings.h"
#include "progressableplugin.h"
#include "QRegularExpression"
#include <QIcon>
#include "imagepluginerrorutil.h"

/**
 * @brief The BingPlugin class is used for downloading images from the bing web search and saving to disk
 */
class BingPlugin : public QObject, ImageLoaderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.BingPlugin" FILE "BingPlugin.json")
    Q_INTERFACES(ImageLoaderPlugin)

private:
    QSharedPointer<BingSettings> pluginSettings;
    QScopedPointer<QProcess> m_process;
    ProgressablePlugin *m_receiver;
    // in case something goes wrong (could be read from command line)
    bool m_success = true;
    int m_imageCount;
    QString m_errorOutPutBuffer;
    QStringList m_labels;

    int m_progress = 0;
    static constexpr auto PLUGIN_ICON = ":/bingicon.svg";
    QString createCommandlineString(const QString &path, int imageCount, const QStringList &label);

public:
    /**
      * @brief loadImages loads images through the Bing API
      * @param path to save the images to
      * @param receiver takes status updates
      * @param imageCount count of images to download
      * @param label list of labels to download images of
      * @return
      */
    bool
    loadImages(const QString &path, ProgressablePlugin *receiver, int imageCount, const QStringList &label) override;

    /**
     * @brief getConfigurationWidget returns a widget in which the Plugin can be configured
     * @return the configuration widget
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

    /**
     * @brief getPluginIcon returns the Icon of the Plugin
     * @return the plugin Icon
     */
    QSharedPointer<QIcon> getPluginIcon() override;

private slots:
    void slot_abort();
    void slot_readOutPut();
    void slot_pluginFinished();
    void slot_readErrorOutPut();


};
//! [0]

#endif
