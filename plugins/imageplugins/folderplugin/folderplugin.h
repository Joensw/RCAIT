/**
 * @file folderplugin.h
 *
 * @brief contains class FolderPlugin
 */
#ifndef FOLDERPLUGIN_H
#define FOLDERPLUGIN_H



#include "folderconfigwidget.h"

#include "imageloaderplugin.h"
#include "plugin.h"
#include "progressableplugin.h"
#include <QDir>
#include <QObject>
#include <QtWidgets/QWidget>
#include <QtPlugin>
#include <QStringBuilder>

/**
 * @brief The FolderPlugin class is an ImageLoaderPlugin that uses existing folders as image sources.
 *
 */
class FolderPlugin : public QObject, ImageLoaderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.FolderPlugin" FILE "FolderPlugin.json")
    Q_INTERFACES(ImageLoaderPlugin)

public:
    /**
     * @brief loadImages loads images from a folder/subfolders.
     *
     * @param path target directory path
     * @param receiver to receive progress and status messages
     * @param imageCount ignored by this plugin
     * @param label ignored by this plugin
     * @return true if loading was successful
     */
    bool loadImages(const QString &path, ProgressablePlugin *receiver, int /*imageCount*/, const QStringList &/*label*/) override;

    /**
     * @brief getConfigurationWidget gets config widget of plugin.
     *
     * @return config widget
     */
    QWidget *getConfigurationWidget() override;

    /**
     * @brief saveConfiguration saves settings of config widget.
     *
     */
    void saveConfiguration() override;

    /**
     * @brief init initializes plugin.
     *
     */
    void init() override;

    /**
     * @brief getName gets name of plugin.
     *
     * @return plugin name
     */
    QString getName() override;

    /**
     * @brief getInputWidget gets widget for plugin specific input.
     *
     * @return input widget
     */
    QWidget*  getInputWidget() override;

private slots:
    void slot_abort();

private:
    FolderConfigwidget* mConfigWidget;
    int mode = 0;
    QString imageDir;
    bool abort = false;

    [[nodiscard]] bool addLabel(const QStringList &images, const QDir &in, QDir out) const;

};

#endif // FOLDERPLUGIN_H
