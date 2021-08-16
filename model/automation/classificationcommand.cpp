#include "classificationcommand.h"

#include <classificationpluginmanager.h>


ClassificationCommand::ClassificationCommand(QVariantMap map, QString trainDataSetPath, QString workingDir, ProgressablePlugin* receiver)
{
    mImagePath = map.value("classificationImagePath").toString();
    mModelName = map.value("modelName").toString();
    mAiPluginName = map.value("aiPluginName").toString();
    mTrainDataSetPath = trainDataSetPath;
    mWorkingDir = workingDir;
    mReceiver = receiver;




    if (mImagePath.isNull() || mModelName.isNull() || mAiPluginName.isNull()){
        parsingFailed = true;
        return;
    }

    QWidget* inputWidget = mPluginManager.getInputWidget(mAiPluginName);

    auto end = map.end();
    for(auto it = map.begin(); it != end; ++it){
        const char* charstring = it.key().toUtf8().data();
        inputWidget->setProperty(charstring, it.value());
    }
    mPluginManager.saveConfiguration(mAiPluginName);
}

bool ClassificationCommand::execute()
{
    if(parsingFailed) return false;
    mResult = mPluginManager.classify(mAiPluginName, mImagePath, mTrainDataSetPath, mWorkingDir, mModelName, mReceiver);
    slot_saveResult();
    return true;
}

void ClassificationCommand::slot_saveResult()
{
    if (mResult == nullptr){
        //emit sig_failed() or something
        return;
    }
    emit sig_saveResult(mResult);
}
