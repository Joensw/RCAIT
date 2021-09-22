/**
 * @file googleplugin.h
 *
 * @brief contains the googlePlugin class
 */
#ifndef GooglePLUGIN_H
#define GooglePLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QSettings>
#include <QLineEdit>
#include <QProcess>
#include <QStringBuilder>
#include <QProcessEnvironment>
#include "imageloaderplugin.h"
#include "googlesettings.h"
#include "progressableplugin.h"
#include "QRegularExpression"


/**
 * @brief The GooglePlugin class is used for downloading images from the google web search and saving to disk
 */
class GooglePlugin : public QObject, ImageLoaderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.GooglePlugin" FILE "GooglePlugin.json")
    Q_INTERFACES(ImageLoaderPlugin)


private:
   GoogleSettings m_googleSettings;
   QWidget *pluginSettings;
   QScopedPointer<QProcess> m_process;
   ProgressablePlugin* m_receiver;
   // in case something goes wrong (could be read from command line)
   bool m_success = true;

    QString createCommandlineString(const QString &path, int imageCount, const QStringList &label);

public:
   /**
     * @brief loadImages loads images through the google API
     * @param path to save the images to
     * @param receiver takes status updates
     * @param imageCount count of images to download
     * @param label list of labels to download images of
     * @return
     */
    bool loadImages(QString path, ProgressablePlugin* receiver ,int imageCount,  QStringList label) override;
    /**
     * @brief getConfigurationWidget returns a widget in which the Plugin can be configured
     * @return the configuration widget
     */
    QWidget* getConfigurationWidget() override;
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
     * @brief getInputWidget is not implemented
     * @return null
     */
    QWidget*  getInputWidget() override;

private slots:
    void slot_abort();
    void slot_readOutPut();
    void slot_pluginFinished();

};
//! [0]

#endif
