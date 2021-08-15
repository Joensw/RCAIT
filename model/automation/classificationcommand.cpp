#include "classificationcommand.h"

#include <classificationpluginmanager.h>


ClassificationCommand::ClassificationCommand(QVariantMap map, Progressable* receiver)
{
    QString imagePath = map.value("classificationImagePath").toString();
    QString modelName = map.value("modelName").toString();
    QString aiPluginName = map.value("aiPluginName").toString();

    if (imagePath.isNull() || modelName.isNull() || aiPluginName.isNull()){
        parsingFailed = true;
        return;
    }

    QWidget* inputWidget = ClassificationPluginManager::getInstance().getInputWidget(aiPluginName);

    auto end = map.end();
    for(auto it = map.begin(); it != end; ++it){
        const char* charstring = it.key().toUtf8().data();
        inputWidget->setProperty(charstring, it.value());
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
    emit sig_saveResult(result);
}
