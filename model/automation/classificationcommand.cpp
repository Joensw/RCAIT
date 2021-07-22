#include "classificationcommand.h"


ClassificationCommand::ClassificationCommand(QVariantMap map, Progressable* receiver)
{
    QString imagePath = map.value("classificationImagePath").toString();
    QString modelName = map.value("modelName").toString();
    QString aiPluginName = map.value("aiPluginName").toString();

    if (imagePath.isNull() || modelName.isNull() || aiPluginName.isNull()){
        parsingFailed = true;
        return;
    }

    mClassifier = new ClassificationThread(receiver, imagePath, modelName, aiPluginName);

}

bool ClassificationCommand::execute()
{
    if(parsingFailed) return false;
    mClassifier->start();
    return true;
}
