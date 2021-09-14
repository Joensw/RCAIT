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
enum TaskState
{
    SCHEDULED,
    PERFORMING,
    FAILED,
    COMPLETED
};

/**
 * @brief The Task class is responsible for executing (multiple) commands.
 *
 */
class Task : public ProgressablePlugin
{
    Q_OBJECT
public:

    /**
     * @brief Task constructs a Task.
     *
     * @param map stores information for commands.
     * @param dataManager source of general information.
     */
    Task(QVariantMap map, DataManager *dataManager, QList<Command*> commandList = {});

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
     * @return true if task is valid (parsing successfull), else false.
     */
    bool isValid();

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

    /**
     * @brief createLoadModel tries to load model with given name, creates new one if it does not exist.
     *
     * @param modelName name of model to load
     * @param pluginName name of plugin
     * @param baseModel name of base model
     */
    void slot_createLoadModel(const QString &modelName, const QString &pluginName, const QString &baseModel = QString());


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
    void sig_progress(int progress);



private:
    const int DEFAULT_SPLIT = 30;

    QString mName;
    TaskState mState = SCHEDULED;
    QString mProjectPath;
    DataManager *mDataManager;
    QList<Command*> mCommandList;
    ResultsExporter* mExporter;

    bool valid = true;
    bool mAbort = false;
    int commandsDone = 0;
};

#endif // TASK_H
