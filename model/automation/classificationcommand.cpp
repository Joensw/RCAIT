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
    connect(mClassifier, &ClassificationThread::finished, this, &ClassificationCommand::slot_saveResult);

}

bool ClassificationCommand::execute()
{
    if(parsingFailed) return false;
    mClassifier->start();
    return true;
}

void ClassificationCommand::slot_saveResult()
{
    ClassificationResult* result = mClassifier->getResult();
    if (result == nullptr){
        //emit sig_failed() or something
        return;
    }
    emit sig_saveResult(*result);
}
