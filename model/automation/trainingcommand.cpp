#include "trainingcommand.h"


TrainingCommand::TrainingCommand(QVariantMap map, Progressable* receiver)
{
    QString imagePath = map.value("trainingImagePath").toString();
    QString modelName = map.value("modelName").toString();
    QString aiPluginName = map.value("aiPluginName").toString();

    if (imagePath.isNull() || modelName.isNull() || aiPluginName.isNull()){
        parsingFailed = true;
        return;
    }

    mTrainer = new TrainingsThread(receiver, imagePath, modelName, aiPluginName);

}

bool TrainingCommand::execute()
{
    if(parsingFailed) return false;
    mTrainer->start();
    return true;
}
