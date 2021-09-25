#include "classificationcommand.h"
#include "imageloadcommand.h"
#include "splitcommand.h"
#include "task.h"
#include "trainingcommand.h"

#include <QApplication>


Task::Task(QVariantMap map, const QList<QSharedPointer<Command>> &commandList)
        : mName(map["taskName"].toString()) {

    if (!commandList.isEmpty()) {
        mCommandList = commandList;
        return;
    }

    QStringList commands = map["taskType"].toStringList();

    if (commands.contains("addProject")) {
        mDataManager.createNewProject(map["projectName"].toString());
    }
    mDataManager.loadProject(map["projectName"].toString());

    if (commands.contains("imageLoad")) {
        auto command = new ImageLoadCommand(map, mDataManager.getProjectImageTempDir(), this);
        QSharedPointer<Command>(command, &QObject::deleteLater);
    }

    if (commands.contains("split")) {
        bool ok;
        int split = map["split"].toInt(&ok);
        if (!ok) split = DEFAULT_SPLIT;

        auto command = new SplitCommand(mDataManager.getProjectImageTempDir(),
                                        mDataManager.getProjectDataSetTrainSubdir(),
                                        mDataManager.getProjectDataSetValSubdir(), split, this);
        mCommandList << QSharedPointer<Command>(command, &QObject::deleteLater);
    }

    if (commands.contains("training")) {
        QString workingDir = mDataManager.createNewWorkSubDir(map["modelName"].toString());
        auto command = new TrainingCommand(map, mDataManager.getProjectDataSetTrainSubdir(),
                                           mDataManager.getProjectDataSetValSubdir(), workingDir, this);
        mCommandList << QSharedPointer<Command>(command, &QObject::deleteLater);
        connect(command, &TrainingCommand::sig_saveResult, this, &Task::slot_saveTrainingResult);
    }

    if (commands.contains("classification")) {
        auto command = new ClassificationCommand(map, mDataManager.getProjectDataSetTrainSubdir(), this);
        mCommandList << QSharedPointer<Command>(command, &QObject::deleteLater);
        connect(command, &ClassificationCommand::sig_saveResult, this, &Task::slot_saveClassificationResult);
    }
    if (mCommandList.isEmpty() && !commands.contains("addProject")) valid = false;

}

void Task::run() {
    emit sig_stateChanged(mName, mState = PERFORMING);

    for (commandsDone = 0; commandsDone < mCommandList.count(); commandsDone++) {
        auto progress = (commandsDone * 100) / mCommandList.size();
        emit sig_progress((int) progress);

        if (mAbort || !mCommandList[commandsDone]->execute()) {
            emit sig_stateChanged(mName, mState = FAILED);
            return;
        }
    }

    emit sig_stateChanged(mName, mState = COMPLETED);
    emit sig_progress(100);
}

QString Task::getName() {
    return mName;
}

TaskState Task::getState() {
    return mState;
}

void Task::resetTask() {
    mState = SCHEDULED;
    mAbort = false;
}

bool Task::isValid() const {
    return valid;
}

void Task::abort() {
    mAbort = true;
    emit sig_pluginAborted();
    emit sig_progress(100);
    forever {
        if (mState == FAILED || mState == COMPLETED || mState == SCHEDULED) return;
        QApplication::processEvents();
        QThread::sleep(1);
    }
}

void Task::slot_makeProgress(int progress) {
    auto localProgress = (commandsDone * 100 + progress) / (mCommandList.size());
    emit sig_progress((int) localProgress);
}

void Task::slot_saveTrainingResult(TrainingResult *result) {
    emit sig_trainingResultUpdated(result);
}

void Task::slot_saveClassificationResult(ClassificationResult *result) {
    emit sig_classificationResultUpdated(result);
}
