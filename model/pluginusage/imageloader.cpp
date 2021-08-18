#include "model/pluginusage/imageloader.h"

ImageLoader::ImageLoader()
{

}

void ImageLoader::loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir)
{
    m_worker = new ImageSearchThread((ProgressablePlugin*) this, tempImageDir,pluginName,count, labels);
    m_worker->moveToThread(&imageloadThread);
    connect(&imageloadThread, &QThread::finished, m_worker, &QObject::deleteLater);
    connect(&imageloadThread, &QThread::finished, this, &ImageLoader::handleResults);
    connect(this, &ImageLoader::operate, m_worker, &ImageSearchThread::loadImages);
    connect(this, &ImageLoader::sig_pluginFinished, this, &ImageLoader::handleResults);
    imageloadThread.start();
}

void ImageLoader::load()
{
    emit sig_progress(0);
    emit operate();

}


void ImageLoader::handleResults() {
    delete m_worker;
    emit sig_progress(100);
    emit sig_imagesReady();
    qDebug() << "Plugin finished and thread deleted";
    //if this object is not deleted threads never die and the signal operate starts all created threads
    delete this;
}

void ImageLoader::slot_makeProgress(int progress)
{
     emit sig_progress(progress);
}
