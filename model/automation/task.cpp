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

    if (!list.isEmpty()){
        mCommandList = list;
        return;
    }

    QStringList commands = map.value("taskType").toStringList();

    if (commands.contains("addProject")){
        mDataManager->createNewProject(map.value("projectName").toString());
    }
    mDataManager->loadProject(map.value("projectName").toString());

    if (commands.contains("imageLoad")) {
        ImageLoadCommand* command = new ImageLoadCommand(map, mDataManager->getProjectImageTempDir(), this);
        mCommandList.append(command);
    }

    if (commands.contains("split")) {
        bool ok;
        int split = map.value("split").toInt(&ok);
        if(!ok) split = DEFAULT_SPLIT;

        SplitCommand* command = new SplitCommand(mDataManager->getProjectImageTempDir(),mDataManager->getProjectDataSetTrainSubdir(), mDataManager->getProjectDataSetValSubdir(), split, this);
        mCommandList.append(command);
    }

    if (commands.contains("training")) {
        QString workingDir = mDataManager->createNewWorkSubDir("working_dir");
        mDataManager->saveLastWorkingDirectoryOfModel(map.value("projectName").toString(), map.value("modelName").toString(), workingDir);
        TrainingCommand* command = new TrainingCommand(map, mDataManager->getProjectDataSetTrainSubdir(), mDataManager->getProjectDataSetValSubdir(), workingDir, this);
        mCommandList.append(command);
        connect(command, &TrainingCommand::sig_saveResult, this, &Task::slot_saveTrainingResult);
    }

    if (commands.contains("classification")) {
        QString workingDir =  mDataManager->recallLastWorkingDirectoryOfModel(map.value("projectName").toString(), map.value("modelName").toString());
        ClassificationCommand* command = new ClassificationCommand(map, mDataManager->getProjectDataSetTrainSubdir(), workingDir, this);
        mCommandList.append(command);
        connect(command, &ClassificationCommand::sig_saveResult, this, &Task::slot_saveClassificationResult);
    }
    if(mCommandList.isEmpty() && !commands.contains("addProject")) valid = false;

}

void Task::run()
{
    mState = PERFORMING;
    emit sig_stateChanged(mName, mState);
    for (commandsDone = 0; commandsDone < mCommandList.count(); commandsDone++){
        emit sig_progress((commandsDone * 100) / (mCommandList.size()));
        if (mAbort){
            mState = FAILED;
            emit sig_stateChanged(mName, mState);
            return;
        }
        if (!mCommandList.at(commandsDone)->execute()) {
            mState = FAILED;
            emit sig_stateChanged(mName, mState);
            return;
        }
    }

    mState = COMPLETED;
    emit sig_stateChanged(mName, mState);
    emit sig_progress(100);
}



QString Task::getName()
{
    return mName;
}

TaskState Task::getState()
{
    return mState;
}

void Task::resetTask()
{
    mState = SCHEDULED;
    mAbort = false;
}

bool Task::isValid()
{
    return valid;
}

void Task::abort()
{
    mAbort = true;
    emit sig_pluginAborted();
    emit sig_progress(100);
    while (true){
        if (mState == FAILED || mState == COMPLETED || mState == SCHEDULED) return;
        QApplication::processEvents();
        QThread::sleep(1);
    }
}

void Task::slot_makeProgress(int progress)
{
    int localProgress = (commandsDone * 100 + progress) / (mCommandList.size());
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
