#include "trainingcommand.h"

#include <classificationpluginmanager.h>


TrainingCommand::TrainingCommand(QVariantMap map, QString trainDataSetPath, QString validationDataSetPath, QString workingDir, ProgressablePlugin* receiver)
{
    mAiPluginName = map.value("aiPluginName").toString();
    mModelName = map.value("modelName").toString();
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
        const char* charstring = it.key().toUtf8().data();
        if (mInputWidget->property(charstring).isValid()){
            mInputOptions.insert(it.key(), it.value());
        }
    }

    mAugmentationWidget = mPluginManager.getDataAugmentationInputWidget(mAiPluginName);
    // getting all property names of augmentation widget
    for(auto it = map.begin(); it != end; ++it){
        const char* charstring = it.key().toUtf8().data();
        if (mAugmentationWidget->property(charstring).isValid()){
            mAugmentationOptions.insert(it.key(), it.value());
        }
    }
}

bool TrainingCommand::execute()
{
    if(parsingFailed) return false;
    // setting properties
    auto endInput = mInputOptions.end();
    for (auto it = mInputOptions.begin(); it != endInput; ++it){
        const char* charstring = it.key().toUtf8().data();
        mInputWidget->setProperty(charstring, it.value());
    }
    auto endAutomation = mAugmentationOptions.end();
    for (auto it = mAugmentationOptions.begin(); it != endAutomation; ++it){
        const char* charstring = it.key().toUtf8().data();
        mAugmentationWidget->setProperty(charstring, it.value());
    }

    mResult = mPluginManager.train(mAiPluginName, mModelName, mTrainDataSetPath, mValidationDataSetPath, mWorkingDir, mReceiver);
    if (mResult == nullptr){
        return false;
    }
    emit sig_saveResult(mResult);
    return true;
}

