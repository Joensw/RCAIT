#include "trainingcommand.h"

#include <classificationpluginmanager.h>


TrainingCommand::TrainingCommand(QVariantMap map, Progressable* receiver)
{
    QString imagePath = map.value("trainingImagePath").toString();
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


    mTrainer = new TrainingsThread(receiver, imagePath, modelName, aiPluginName);
    connect(mTrainer, &TrainingsThread::finished, this, &TrainingCommand::slot_saveResult);

}

bool TrainingCommand::execute()
{
    if(parsingFailed) return false;
    mTrainer->start();
    return true;
}

void TrainingCommand::slot_saveResult()
{
    TrainingResult* result = mTrainer->getResult();
    if (result == nullptr){
        //emit sig_failed() or something
        return;
    }
    emit sig_saveResult(*result);
}

