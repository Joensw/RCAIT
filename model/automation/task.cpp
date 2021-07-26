#include "classificationcommand.h"
#include "imageloadcommand.h"
#include "task.h"
#include "trainingcommand.h"

#include <QApplication>


Task::Task(QVariantMap map, DataManager *dataManager, QList<Command*> list)
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

    if (!list.isEmpty()){
        mCommandList = list;
        return;
    }

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
    if (commandsDone == 0){
        mState = PERFORMING;
        emit sig_stateChanged(mState);
    }
    if (commandsDone >= mCommandList.count()){
        mState = COMPLETED;
        emit sig_stateChanged(mState);
        return;
    }
    int tempCommandsDone = commandsDone;
    if (!mCommandList.at(commandsDone)->execute()) {
        mState = FAILED;
        emit sig_stateChanged(mState);
        return;
    }
    while(tempCommandsDone == commandsDone){
        QApplication::processEvents();
        QThread::sleep(1);
    }
    run();
}



QString Task::getName()
{
    return mName;
}

TaskState Task::getState()
{
    return mState;
}

bool Task::isValid()
{
    return valid;
}

void Task::slot_makeProgress(int progress)
{
    int localProgress = (commandsDone * 100 + progress) / (mCommandList.size() * 100);
    if(progress == 100) commandsDone++;
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
