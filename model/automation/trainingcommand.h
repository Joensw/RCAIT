#ifndef TRAININGCOMMAND_H
#define TRAININGCOMMAND_H

#include "command.h"

#include <pluginusage/trainingsthread.h>

class TrainingCommand : public Command
{
public:
    TrainingCommand(QVariantMap map);

private:
    TrainingsThread *mTrainer;
};

#endif // TRAININGTASK_H
