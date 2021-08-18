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

    QWidget* inputWidget = mPluginManager.getInputWidget(mAiPluginName);
    auto end = map.end();
    for(auto it = map.begin(); it != end; ++it){
        const char* charstring = it.key().toUtf8().data();
        inputWidget->setProperty(charstring, it.value());
    }

    QWidget* automationWidget = mPluginManager.getDataAugmentationInputWidget(mAiPluginName);
    for(auto it = map.begin(); it != end; ++it){
        const char* charstring = it.key().toUtf8().data();
        automationWidget->setProperty(charstring, it.value());
    }
}

bool TrainingCommand::execute()
{
    if(parsingFailed) return false;
    mResult = mPluginManager.train(mAiPluginName, mModelName, mTrainDataSetPath, mValidationDataSetPath, mWorkingDir, mReceiver);
    if (mResult == nullptr){
        return false;
    }
    emit sig_saveResult(mResult);
    return true;
}

