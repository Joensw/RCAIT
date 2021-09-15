#include "classificationcommand.h"

#include <classificationpluginmanager.h>


ClassificationCommand::ClassificationCommand(QVariantMap map, const QString &trainDataSetPath, ProgressablePlugin* receiver)
{
    mProjectName = map.value("projectName").toString();
    mImagePath = map.value("classificationImagePath").toString();
    mModelName = map.value("modelName").toString();
    mAiPluginName = map.value("aiPluginName").toString();
    mTrainDataSetPath = trainDataSetPath;
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
    mWorkingDir =  mDataManager.recallLastWorkingDirectoryOfModel(mProjectName, mModelName);
    mResult = mPluginManager.classify(mAiPluginName, mImagePath, mTrainDataSetPath, mWorkingDir, mModelName, mReceiver);
    if (!mResult->isValid()){
        return false;
    }
    emit sig_saveResult(mResult);
    return true;
}
