
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
class FlickrPlugin : public QObject, ImageLoaderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.FlickrPlugin" FILE "FlickrPlugin.json")
    Q_INTERFACES(ImageLoaderPlugin)

public:
    bool loadImages(QString path, ProgressablePlugin* receiver ,int imageCount,  QStringList label) override;
    QWidget* getConfigurationWidget() override;
    void saveConfiguration() override;
    void init() override;
    QString getName() override;
    QWidget*  getInputWidget() override;

private:
   FlickrSettings m_flickrSettings;
   QWidget *pluginSettings;
   QScopedPointer<QProcess> m_process;
   ProgressablePlugin* m_receiver;
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
