#ifndef TRAININGCOMMAND_H
#define TRAININGCOMMAND_H

#include "command.h"

#include <pluginusage/trainingsthread.h>

class TrainingCommand : public Command
{
    Q_OBJECT
public:
    TrainingCommand(QVariantMap map);
    bool execute() override;

signals:
    void sig_saveResult(TrainingResult result);

private:
    TrainingsThread *mTrainer;


};

#endif // TRAININGTASK_H
