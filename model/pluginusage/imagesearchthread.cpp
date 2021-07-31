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
    m_receiver = (ProgressablePlugin*) receiver;


}

void ImageSearchThread::loadImages() {
    m_imageLoaderPluginManager.loadImages(m_imagePath, m_receiver, m_pluginName, m_count, m_labels);
}


    //m_imageLoaderPluginManager.loadImages(m_imagePath, m_receiver, m_pluginName, m_count, m_labels);



