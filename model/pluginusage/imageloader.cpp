#include "model/pluginusage/imageloader.h"
#include <QtConcurrent/QtConcurrent>

ImageLoader::ImageLoader()= default;

void ImageLoader::loadInputImages(int count, QStringList labels, QString pluginName, QString tempImageDir)
{
    connect(this, &ImageLoader::sig_pluginFinished, this, &ImageLoader::slot_handleResults);
    auto task = QtConcurrent::run(&ImageLoaderPluginManager::loadImages, &mManager, tempImageDir, (ProgressablePlugin*) this, pluginName, count, labels);
    Q_UNUSED(task);
    emit sig_progress(0);
}



void ImageLoader::slot_handleResults() {
    emit sig_progress(100);
    emit sig_imagesReady();
    //if this object is not deleted threads never die and the signal operate starts all created threads
    qDebug() << "Plugin finished and thread deleted";
}

void ImageLoader::slot_makeProgress(int progress)
{
     emit sig_progress(progress);
}
