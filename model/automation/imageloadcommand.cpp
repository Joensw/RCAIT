#include "imageloadcommand.h"
#include "imageloaderpluginmanager.h"


ImageLoadCommand::ImageLoadCommand(QVariantMap map, QString imagePath, ProgressablePlugin* receiver)
{   bool ok;

    QString imagePluginName = map.value("imagePluginName").toString();
    int count = map.value("count").toInt(&ok);
    QStringList labels = map.value("labels").toStringList();

    if (imagePath.isNull() || imagePluginName.isNull() || !ok || labels.isEmpty()){
        parsingFailed = true;
        return;
    }

    QWidget* inputWidget = ImageLoaderPluginManager::getInstance().getConfigurationWidget(imagePluginName);

    auto end = map.end();
    for(auto it = map.begin(); it != end; ++it){
        const char* charstring = it.key().toUtf8().data();
        inputWidget->setProperty(charstring, it.value());
    }

    ImageLoaderPluginManager::getInstance().saveConfiguration(imagePluginName);

    mCount = count;
    mLabels = labels;
    mPluginName = imagePluginName;
    mPath = imagePath;


   mImageSearcher = new ImageSearchThread(receiver, imagePath, mPluginName, count, labels);
//   connect(mImageSearcher, &ImageLoader::sig_progress, receiver, &Progressable::slot_makeProgress);

}

bool ImageLoadCommand::execute(){
    if(parsingFailed) return false;
    mImageSearcher->loadImages();
    qDebug() << "execute started";
    return true;
}
