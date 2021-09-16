#include "trainingcommand.h"

#include <classificationpluginmanager.h>
#include <datamanager.h>


TrainingCommand::TrainingCommand(QVariantMap map,const QString &trainDataSetPath, const QString &validationDataSetPath,const QString &workingDir, ProgressablePlugin* receiver)
{
    mProjectName = map.value("projectName").toString();
    mAiPluginName = map.value("aiPluginName").toString();
    mModelName = map.value("modelName").toString();
    mBaseModel = map.value("baseModel").toString();
    mTrainDataSetPath = trainDataSetPath;
    mValidationDataSetPath = validationDataSetPath;
    mWorkingDir = workingDir;
    mReceiver = receiver;

    if (mModelName.isNull() || mAiPluginName.isNull()){
        parsingFailed = true;
        return;
    }

    mInputWidget = mPluginManager.getInputWidget(mAiPluginName);
    // getting all property names of input widget
    auto end = map.end();
    for(auto it = map.begin(); it != end; ++it){
        if (mInputWidget->property(it.key().toUtf8().data()).isValid()){
            mInputOptions.insert(it.key(), it.value());
        }
    }

    mAugmentationWidget = mPluginManager.getDataAugmentationInputWidget(mAiPluginName);
    // getting all property names of augmentation widget
    for(auto it = map.begin(); it != end; ++it){
        if (mAugmentationWidget->property(it.key().toUtf8().data()).isValid()){
            mAugmentationOptions.insert(it.key(), it.value());
        }
    }
}

bool TrainingCommand::execute()
{
    if(parsingFailed) return false;

    // creating/loading model
    if (!mBaseModel.isNull()){
        mDataManager.createNewModel(mModelName, mAiPluginName, mBaseModel);
    }
    mDataManager.loadModel(mModelName, mAiPluginName);

    // setting properties
    auto endInput = mInputOptions.end();
    for (auto it = mInputOptions.begin(); it != endInput; ++it){
        mInputWidget->setProperty(it.key().toUtf8().data(), it.value());
    }
    auto endAutomation = mAugmentationOptions.end();
    for (auto it = mAugmentationOptions.begin(); it != endAutomation; ++it){
        mAugmentationWidget->setProperty(it.key().toUtf8().data(), it.value());
    }

    mResult = mPluginManager.train(mAiPluginName, mModelName, mTrainDataSetPath, mValidationDataSetPath, mWorkingDir, mReceiver);
    if (!mResult->isValid()){
        return false;
    }
    mDataManager.saveLastWorkingDirectoryOfModel(mProjectName, mModelName, mWorkingDir);

    emit sig_saveResult(mResult);
    return true;
}

