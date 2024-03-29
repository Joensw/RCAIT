#include "imageloader.h"

ImageLoader::ImageLoader()= default;

void ImageLoader::loadInputImages(int count, const QStringList &labels, const QString &pluginName, const QString &tempImageDir)
{
    auto watcher = new QFutureWatcher<bool>;
    connect(watcher, &QFutureWatcher<bool>::finished, this, &ImageLoader::slot_handleResults);
    connect(watcher, &QFutureWatcher<bool>::finished, watcher, &QFutureWatcher<bool>::deleteLater);
    auto task = QtConcurrent::run(&ImageLoaderPluginManager::loadImages, &mManager, tempImageDir, (ProgressablePlugin*) this, pluginName, count, labels);
    watcher->setFuture(task);
    emit sig_progress(0);
}



void ImageLoader::slot_handleResults() {
    emit sig_progress(100);
    emit sig_imagesReady();
}

void ImageLoader::slot_makeProgress(int progress)
{
     emit sig_progress(progress);
}
