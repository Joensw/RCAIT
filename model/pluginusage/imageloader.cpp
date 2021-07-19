#include "model/pluginusage/imageloader.h"

ImageLoader::ImageLoader()
{

}

void ImageLoader::loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir)
{
    ImageSearchThread *worker = new ImageSearchThread((ProgressablePlugin*) this, tempImageDir,pluginName,count, labels);
    worker->moveToThread(&imageloadThread);
    connect(&imageloadThread, &QThread::finished, worker, &QObject::deleteLater);
    connect(this, &ImageLoader::operate, worker, &ImageSearchThread::loadImages);
    connect(worker, &ImageSearchThread::resultReady, this, &ImageLoader::handleResults);
    imageloadThread.start();
    emit operate();


     //m_imageSearchThread = new ImageSearchThread((ProgressablePlugin*) this, tempImageDir,pluginName,count, labels);
    //m_imageSearchThread->start();
}

void ImageLoader::handleResults(const QString &) {

}

