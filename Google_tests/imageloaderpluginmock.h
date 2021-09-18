#ifndef IMAGELOADERPLUGINMOCK_H
#define IMAGELOADERPLUGINMOCK_H
#include <QObject>
#include <QtPlugin>
#include <QSettings>
#include <QLineEdit>
#include <QProcess>
#include <QProcessEnvironment>
#include "imageloaderplugin.h"
#include "progressableplugin.h"

class ImageLoaderPluginMock : public QObject, ImageLoaderPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.FlickrPlugin" FILE "ImageLoaderPluginMock.json")
    Q_INTERFACES(ImageLoaderPlugin)

public:

    bool loadImages(QString path, ProgressablePlugin* receiver ,int imageCount,  QStringList label) override;
    QWidget* getConfigurationWidget() override;
    void saveConfiguration() override;
    void init() override;
    QString getName() override;
    QWidget*  getInputWidget() override;
    inline static const QString PLUGIN_NAME = "testplugin";

private:

   QWidget *pluginSettings = new QWidget();
   QWidget *inputWidget = new QWidget();
   QScopedPointer<QProcess> m_process;
   ProgressablePlugin* m_receiver;
   bool m_success = true;


private slots:
    void slot_abort();
    void slot_readOutPut();
    void slot_pluginFinished();



};

#endif
