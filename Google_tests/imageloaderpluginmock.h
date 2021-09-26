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

class ImageLoaderPluginMock : public QObject, ImageLoaderPlugin {
Q_OBJECT
    Q_PLUGIN_METADATA(IID "de.Fraunhofer.IOSB.RCAIT.FlickrPlugin" FILE "ImageLoaderPluginMock.json")
    Q_INTERFACES(ImageLoaderPlugin)

public:

    bool
    loadImages(const QString &path, ProgressablePlugin *receiver, int imageCount, const QStringList &label) override;

    QSharedPointer<QWidget> getConfigurationWidget() override;

    void saveConfiguration() override;

    void init() override;

    QString getName() override;

    QSharedPointer<QWidget> getInputWidget() override;

    static constexpr auto PLUGIN_NAME = "testplugin";

    QSharedPointer<QIcon> getPluginIcon() override;

private:
    QSharedPointer<QWidget> pluginSettings = {new QWidget, &QObject::deleteLater};
    QSharedPointer<QWidget> inputWidget = {new QWidget, &QObject::deleteLater};
    QScopedPointer<QProcess> m_process;
    ProgressablePlugin *m_receiver;
    bool m_success = true;


private slots:

    void slot_abort();

    void slot_readOutPut();

    void slot_pluginFinished();


};

#endif
