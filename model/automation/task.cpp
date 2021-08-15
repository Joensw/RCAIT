#include "classificationcommand.h"
#include "imageloadcommand.h"
#include "splitcommand.h"
#include "task.h"
#include "trainingcommand.h"

#include <QApplication>


Task::Task(QVariantMap map, DataManager *dataManager, QList<Command*> list)
{
    mExporter = new ResultsExporter();

    mDataManager = dataManager;
    mName = map.value("taskName").toString();

    QStringList commands = map.value("taskType").toStringList();
    if (commands.isEmpty()){
        valid = false;
    }

    if (commands.contains("addProject")){
        mDataManager->createNewProject(map.value("projectName").toString());
    }
    mDataManager->loadProject(map.value("projectName").toString());

    if (!list.isEmpty()){
        mCommandList = list;
        return;
    }

    if (commands.contains("imageLoad")) {
        ImageLoadCommand* command = new ImageLoadCommand(map, mDataManager->getProjectTempDir(), this);
        mCommandList.append(command);
    }

    if (commands.contains("split")) {
        bool ok;
        int split = map.value("split").toInt(&ok);
        if(!ok) split = DEFAULT_SPLIT;

        SplitCommand* command = new SplitCommand(mDataManager->getProjectTempDir(),mDataManager->getProjectDataSetDir(), split, this);
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
        emit sig_stateChanged(mName, mState);
    }
    if (commandsDone == mCommandList.count()){
        mState = COMPLETED;
        emit sig_stateChanged(mName, mState);
        return;
    }
    if (commandsDone > mCommandList.count()){
        mState = FAILED;
        emit sig_stateChanged(mName, mState);
        commandsDone = 0;
        return;
    }
    int tempCommandsDone = commandsDone;
    if (!mCommandList.at(commandsDone)->execute()) {
        mState = FAILED;
        emit sig_stateChanged(mName, mState);
        return;
    }

    while(tempCommandsDone == commandsDone){
        QApplication::processEvents();
        QThread::sleep(4);
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

void Task::abort()
{
    commandsDone = mCommandList.size() + 1;
    emit sig_pluginAborted();
    emit sig_progress(100);
}

void Task::slot_makeProgress(int progress)
{
    int localProgress = (commandsDone * 100 + progress) / (mCommandList.size());
    if(progress == 100) commandsDone++;
    emit sig_progress(localProgress);
}

void Task::slot_saveTrainingResult(TrainingResult *result)
{
    mExporter->slot_save_TrainingResult(result);
}

void Task::slot_saveClassificationResult(ClassificationResult *result)
{
    mExporter->slot_save_ClassificationResult(result);
}
