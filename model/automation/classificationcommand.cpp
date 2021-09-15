#include "classificationcommand.h"

#include <classificationpluginmanager.h>


ClassificationCommand::ClassificationCommand(QVariantMap map, const QString &trainDataSetPath, const QString &workingDir, ProgressablePlugin* receiver)
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

}

bool ClassificationCommand::execute()
{
    if(parsingFailed) return false;

    // loading model
    mDataManager.loadModel(mModelName, mAiPluginName);

    mResult = mPluginManager.classify(mAiPluginName, mImagePath, mTrainDataSetPath, mWorkingDir, mModelName, mReceiver);
    if (!mResult->isValid()){
        return false;
    }
    emit sig_saveResult(mResult);
    return true;
}
