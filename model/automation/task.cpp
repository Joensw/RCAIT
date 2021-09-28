#include "classificationcommand.h"
#include "imageloadcommand.h"
#include "splitcommand.h"
#include "task.h"
#include "trainingcommand.h"

#include <QApplication>

/**
 * @brief This enum contains all types of supported commands.
 *
 * New command types can be inserted here.
 */
enum CommandType {
    IMAGELOAD,
    SPLIT,
    TRAINING,
    CLASSIFICATION,
    $COUNT
};

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

    static std::array<QString, $COUNT> COMMANDTYPE2STRING = {
        "imageLoad",
        "split",
        "training",
        "classification"
    };

    for (int i = 0; i < $COUNT; i++){
        if (commands.contains(COMMANDTYPE2STRING[i])){
            insertCommand(i, map);
        }
    }

    if (mCommandList.isEmpty() && !commands.contains("addProject")) valid = false;
}

void Task::insertCommand(int type, QVariantMap map){
    Command* command;
    switch (type) {
        case IMAGELOAD:
            command = new ImageLoadCommand(map, this);
            break;
        case SPLIT:
            command = new SplitCommand(map, this);
            break;
        case TRAINING:
            command = new TrainingCommand(map, this);
            connect((TrainingCommand*) command, &TrainingCommand::sig_saveResult, this, &Task::slot_saveTrainingResult);
            break;
        case CLASSIFICATION:
            command = new ClassificationCommand(map, this);
            connect((ClassificationCommand*) command, &ClassificationCommand::sig_saveResult, this, &Task::slot_saveClassificationResult);
            break;
        default:
            qDebug() << "Attempted to set unknown command type";
            break;
    }
    mCommandList << QSharedPointer<Command>(command, &QObject::deleteLater);
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

void Task::slot_saveTrainingResult(const QSharedPointer<TrainingResult> &result) {
    emit sig_trainingResultUpdated(result);
}

void Task::slot_saveClassificationResult(const QSharedPointer<ClassificationResult> &result) {
    emit sig_classificationResultUpdated(result);
}
