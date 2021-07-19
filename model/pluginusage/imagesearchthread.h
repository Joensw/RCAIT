#ifndef RCAIT_IMAGESEARCHTHREAD_H
#define RCAIT_IMAGESEARCHTHREAD_H

#include <QThread>
#include <pluginusage/progressableplugin.h>
#include "imageloaderpluginmanager.h"

//ImageSearchThread cannot inherit from QThread and ProgressablePlugin since both inherit from QObject
//Thread implementation from example 1 https://doc.qt.io/qt-5/qthread.html
class ImageSearchThread :  public QObject {
    Q_OBJECT



public:
    ImageSearchThread(Progressable* receiver, QString imagePath, QString pluginName, int count, QStringList labels);

public slots:
    void loadImages();


signals:
    void resultReady(const QString &s);

private:
        ProgressablePlugin* m_receiver;
        QString m_imagePath;
        QString m_pluginName;
        int m_count;
        QStringList m_labels;
        volatile bool* stopped;
        ImageLoaderPluginManager& m_imageLoaderPluginManager = ImageLoaderPluginManager::getInstance();;

};


#endif //RCAIT_IMAGESEARCHTHREAD_H
