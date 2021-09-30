#include "trainingcommand.h"


TrainingCommand::TrainingCommand(QVariantMap map, ProgressablePlugin *receiver)
        : mProjectName(map["projectName"].toString()),
          mAiPluginName(map["aiPluginName"].toString()),
          mModelName(map["modelName"].toString()),
          mBaseModel(map["baseModel"].toString()),
          mTrainDataSetPath(mDataManager.getProjectDataSetTrainSubdir()),
          mValidationDataSetPath(mDataManager.getProjectDataSetValSubdir()),
          mWorkingDir(mDataManager.createNewWorkSubDir(map["modelName"].toString())),
          mReceiver(receiver) {

    if (mModelName.isNull() || mAiPluginName.isNull()) {
        parsingFailed = true;
        return;
    }

    mInputWidget = mPluginManager.getInputWidget(mAiPluginName);
    if (mInputWidget) {
        // getting all property names of input widget
        for (const auto &[key, value]: MapAdapt(map)) {
            if (mInputWidget->property(key.toUtf8().data()).isValid())
                mInputOptions[key] = value;
        }
    }

    mAugmentationWidget = mPluginManager.getDataAugmentationInputWidget(mAiPluginName);
    if (!mAugmentationWidget) return;
    // getting all property names of augmentation widget
    for (const auto &[key, value]: MapAdapt(map)) {
        if (mAugmentationWidget->property(key.toUtf8().data()).isValid())
            mAugmentationOptions[key] = value;
    }
}

bool TrainingCommand::execute() {
    if (parsingFailed) return false;

    // creating/loading model
    if (!mBaseModel.isNull()) {
        mDataManager.createNewModel(mModelName, mAiPluginName, mBaseModel);
    }
    mDataManager.loadModel(mModelName, mAiPluginName);

    // setting properties
    for (const auto &[key, value]: MapAdapt(mInputOptions)) {
        mInputWidget->setProperty(key.toUtf8().data(), value);
    }
    for (const auto &[key, value]: MapAdapt(mAugmentationOptions)) {
        mAugmentationWidget->setProperty(key.toUtf8().data(), value);
    }

    mResult = mPluginManager.train(mAiPluginName, mModelName, mTrainDataSetPath, mValidationDataSetPath, mWorkingDir,
                                   mReceiver);

    if (!mResult->isValid()) return false;

    mDataManager.saveLastWorkingDirectoryOfModel(mProjectName, mModelName, mWorkingDir);

    emit sig_saveResult(mResult);
    return true;
}

