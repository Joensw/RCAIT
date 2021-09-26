#ifndef TASK_H
#define TASK_H

#include "command.h"

#include <pluginusage/progressable.h>

#include <datamanager.h>
#include "resultsexporter.h"

/**
 * @brief The TaskState enum is an enumeration of task states.
 *
 */
enum TaskState {
    NOT_SCHEDULED,
    SCHEDULED,
    PERFORMING,
    FAILED,
    COMPLETED
};

static constexpr CE_String StateMap[] = {
        "Not_Scheduled",
        "Scheduled",
        "Performing",
        "Failed",
        "Completed"
};


/**
 * @brief The Task class is responsible for executing (multiple) commands.
 *
 */
class Task : public ProgressablePlugin {
Q_OBJECT
public:

    /**
     * @brief Task constructs a Task.
     *
     * @param map stores information for commands.
     * @param commandList list of the supplied commands.
     */
    explicit Task(QVariantMap map, const QList<QSharedPointer<Command>> &commandList = {});

    /**
     * @brief getName returns name of the Task.
     *
     * @return Task name.
     */
    QString getName();


    /**
     * @brief getState returns state of the Task.
     *
     * @return Task state.
     */
    TaskState getState();

    /**
     * @brief resetTask resets stopped task to standard state.
     *
     */
    void resetTask();

    /**
     * @brief run executes all commands of the Task.
     *
     */
    void run();

    /**
     * @brief isValid returns validity of Task.
     *
     * @return true if task is valid (parsing successful), else false.
     */
    [[nodiscard]] bool isValid() const;

    /**
     * @brief abort aborts the Task.
     */
    void abort();


public slots:

    /**
     * @brief slot_makeProgress defines behavior when accepting progress signals.
     *
     * @param progress number in percent.
     */
    void slot_makeProgress(int progress) override;

    /**
     * @brief slot_saveTrainingResult saves training result.
     *
     * @param result training result.
     */
    void slot_saveTrainingResult(TrainingResult *result);

    /**
     * @brief slot_saveClassificationResult saves classification result.
     *
     * @param result classification result.
     */
    void slot_saveClassificationResult(ClassificationResult *result);

signals:

    /**
     * @brief sig_stateChanged signals changing task state.
     *
     * @param newState new task state.
     */
    void sig_stateChanged(QString name, TaskState newState);

    /**
     * @brief sig_progress signals progress of task.
     *
     * @param progress number in percent.
     */
    void sig_progress(int progress) override;

    /**
     * @brief sig_trainingResultUpdated signals new training result from automation.
     *
     * @param result training result
     */
    void sig_trainingResultUpdated(TrainingResult *result);

    /**
     * @brief sig_classificationResultUpdated signals new classification result from automation.
     *
     * @param result classification result
     */
    void sig_classificationResultUpdated(ClassificationResult *result);


private:
    void insertCommand(int type, QVariantMap map);

    QString mName;
    TaskState mState = SCHEDULED;
    QString mProjectPath;
    DataManager &mDataManager = DataManager::getInstance();
    QList<QSharedPointer<Command>> mCommandList;
    QScopedPointer<ResultsExporter> mExporter;

    bool valid = true;
    bool mAbort = false;
    int commandsDone = 0;
};

#endif // TASK_H
