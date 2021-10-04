#include "task.h"

Task::Task(const QVariantMap &map, const QList<QSharedPointer<Command>> &commandList)
        : mName(map["taskName"].toString()) {

    if (!commandList.isEmpty()) {
        mCommandList = commandList;
        return;
    }

    QStringList commands = map["taskType"].toStringList();

    if (commands.contains(ADD_PROJECT_ENTRY)) {
        mDataManager.createNewProject(map["projectName"].toString());
    }
    if (!mDataManager.loadProject(map["projectName"].toString())) {
        valid = false;
        qWarning() << "Could not load project of task!";
        return;
    }

    static constexpr std::array<CE_String, static_cast<int>(CommandType::$LENGTH)> COMMANDTYPE2STRING = {
            "imageLoad",
            "split",
            "training",
            "classification"
    };

    for (int i = 0; i < static_cast<int>(CommandType::$LENGTH); i++) {
        if (commands.contains(COMMANDTYPE2STRING[i])) {
            insertCommand(static_cast<CommandType>(i), map);
        }
    }

    if (mCommandList.isEmpty() && !commands.contains(ADD_PROJECT_ENTRY)) valid = false;
}

void Task::insertCommand(CommandType type, const QVariantMap &map) {
    Command *command;
    switch (type) {
        case CommandType::IMAGELOAD:
            command = new ImageLoadCommand(map, this);
            break;
        case CommandType::SPLIT:
            command = new SplitCommand(map, this);
            break;
        case CommandType::TRAINING:
            command = new TrainingCommand(map, this);
            connect(dynamic_cast<TrainingCommand*> (command), &TrainingCommand::sig_saveResult, this, &Task::slot_saveTrainingResult);
            break;
        case CommandType::CLASSIFICATION:
            command = new ClassificationCommand(map, this);
            connect(dynamic_cast<ClassificationCommand*> (command), &ClassificationCommand::sig_saveResult, this, &Task::slot_saveClassificationResult);
            break;
        default:
            command = nullptr;
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

QString Task::getName() const {
    return mName;
}

TaskState Task::getState() const {
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

void Task::slot_saveTrainingResult(const QPointer<TrainingResult> &result) {
    emit sig_trainingResultUpdated(result);
}

void Task::slot_saveClassificationResult(const QPointer<ClassificationResult> &result) {
    emit sig_classificationResultUpdated(result);
}
