#include "imageloadcommand.h"



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

    mImageSearcher = new ImageSearchThread((ProgressablePlugin*)receiver, imagePath, imagePluginName, count, labels);

}

bool ImageLoadCommand::execute(){
    if(parsingFailed) return false;
    mImageSearcher->start();
    mImageSearcher->wait();
    return true;
}
