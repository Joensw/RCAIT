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

    QWidget* mInputWidget = mPluginManager.getInputWidget(mAiPluginName);

    // getting all property names of input widget
    auto end = map.end();
    for(auto it = map.begin(); it != end; ++it){
        if (mInputWidget->property(it.key().toUtf8().data()).isValid()){
            mWidgetOptions.insert(it.key(), it.value());
        }
    }
}

bool ClassificationCommand::execute()
{
    if(parsingFailed) return false;

    // setting properties
    auto end = mWidgetOptions.end();
    for (auto it = mWidgetOptions.begin(); it != end; ++it){
        mInputWidget->setProperty(it.key().toUtf8().data(), it.value());
    }

    mResult = mPluginManager.classify(mAiPluginName, mImagePath, mTrainDataSetPath, mWorkingDir, mModelName, mReceiver);
    if (mResult == nullptr){
        return false;
    }
    emit sig_saveResult(mResult);
    return true;
}
