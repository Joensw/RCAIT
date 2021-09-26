#include "classificationcommand.h"

#include <classificationpluginmanager.h>

ClassificationCommand::ClassificationCommand(QVariantMap map, ProgressablePlugin *receiver)
        : mProjectName(map["projectName"].toString()),
          mImagePath(map["classificationImagePath"].toString()),
          mModelName(map["modelName"].toString()),
          mAiPluginName(map["aiPluginName"].toString()),
          mTrainDataSetPath(mDataManager.getProjectDataSetTrainSubdir()),
          mReceiver(receiver) {

    if (mImagePath.isNull() || mModelName.isNull() || mAiPluginName.isNull()) {
        parsingFailed = true;
        return;
    }

}

bool ClassificationCommand::execute() {
    if (parsingFailed) return false;

    // loading model
    mDataManager.loadModel(mModelName, mAiPluginName);
    mWorkingDir = mDataManager.recallLastWorkingDirectoryOfModel(mProjectName, mModelName);
    mResult = mPluginManager.classify(mAiPluginName, mImagePath, mTrainDataSetPath, mWorkingDir, mModelName, mReceiver);
    if (mResult->isValid()) {
        emit sig_saveResult(mResult);
        return true;
    }
    return false;
}
