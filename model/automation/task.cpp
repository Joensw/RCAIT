#include "classificationcommand.h"
#include "imageloadcommand.h"
#include "task.h"
#include "trainingcommand.h"


Task::Task(QVariantMap map, DataManager *dataManager)
{
    mDataManager = dataManager;
    mName = map.value("taskName").toString();

    QStringList commands = map.value("taskType").toStringList();
    if (commands.isEmpty()){
        valid = false;
    }

    if (commands.contains("addProject")){
        mDataManager->createNewProject(map.value("addProject").toString());
    }
    mDataManager->loadProject(map.value("addProject").toString());

    if (commands.contains("imageLoad")) {
        ImageLoadCommand* command = new ImageLoadCommand(map, this);
        mCommandList.append(command);
    }

    if (commands.contains("training")) {
        TrainingCommand* command = new TrainingCommand(map, this);
        mCommandList.append(command);
        connect(command, &TrainingCommand::sig_saveResult, this, &Task::slot_saveTrainingResult);
    }

    if (commands.contains("classification")) {
        ClassificationCommand* command = new ClassificationCommand(map, this);
        mCommandList.append(command);
        connect(command, &ClassificationCommand::sig_saveResult, this, &Task::slot_saveClassificationResult);
    }

}

void Task::run()
{
    for(Command* cmd: mCommandList){
        if(!cmd->execute()){
            mState = FAILED;
            sig_stateChanged(mState);
            //TODO optional parameter "undoOnFail" and the according undo implementation
            return;
        }
        commandsDone++;
    }
}

QString Task::getName()
{
    return mName;
}

bool Task::isValid()
{
    return valid;
}

void Task::slot_makeProgress(int progress)
{
    int localProgress = (commandsDone * 100 + progress) / (mCommandList.size() * 100);
    emit sig_progress(localProgress);
}

void Task::slot_saveTrainingResult(TrainingResult result)
{
    mDataManager->saveTrainingsResult(result);
}

void Task::slot_saveClassificationResult(ClassificationResult result)
{
    mDataManager->saveClassificationResult(result);
}
