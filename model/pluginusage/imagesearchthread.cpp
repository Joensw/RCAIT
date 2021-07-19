#include "imagesearchthread.h"

/*ImageSearchThread::ImageSearchThread(ProgressablePlugin *receiver, QString imagePath, QString pluginName, int count,
                                     QStringList labels) {

}
*/

ImageSearchThread::ImageSearchThread(Progressable *receiver, QString imagePath, QString pluginName, int count, QStringList labels)
{
    //m_receiver = receiver;
    m_imagePath = imagePath;
    m_pluginName = pluginName;
    m_count = count;
    m_labels = labels;


}

void ImageSearchThread::loadImages() {
    m_imageLoaderPluginManager.loadImages(R"(C:\Users\Mr Stealyourgirl\Desktop\ok)", m_receiver, m_pluginName, m_count, m_labels);
    emit resultReady("");

}


    //m_imageLoaderPluginManager.loadImages(m_imagePath, m_receiver, m_pluginName, m_count, m_labels);



