#include "imageloadcommand.h"
#include "imageloaderpluginmanager.h"


ImageLoadCommand::ImageLoadCommand(QVariantMap map, Progressable* receiver)
{
    bool ok;

    QString imagePath = map.value("trainingImagePath").toString();
    QString imagePluginName = map.value("imagePluginName").toString();
    int count = map.value("count").toInt(&ok);
    QStringList labels = map.value("labels").toStringList();

    if (imagePath.isNull() || imagePluginName.isNull() || !ok || labels.isEmpty()){
        parsingFailed = true;
        return;
    }

    QWidget* inputWidget = ImageLoaderPluginManager::getInstance().getInputWidget(imagePluginName);

    auto end = map.end();
    for(auto it = map.begin(); it != end; ++it){
        const char* charstring = it.key().toUtf8().data();
        inputWidget->setProperty(charstring, it.value());
    }


    mImageSearcher = new ImageSearchThread(receiver, imagePath, imagePluginName, count, labels);

}

bool ImageLoadCommand::execute(){
    if(parsingFailed) return false;
    mImageSearcher->loadImages();
    return true;
}
