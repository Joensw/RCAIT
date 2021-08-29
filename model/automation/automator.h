#ifndef AUTOMATOR_H
#define AUTOMATOR_H

#include "task.h"

#include <datamanager.h>

#include <pluginusage/progressable.h>


/**
 * @brief The Automator class for managing task scheduling and execution.
 *
 */
class Automator : public Progressable
{
    Q_OBJECT
public:

    /**
     * @brief Automator constructs a new Automator.
     *
     * @param dataManager source of general information.
     */
    Automator(DataManager *dataManager);

    /**
     * @brief performTasks starts tasks scheduled for execution.
     *
     */
    void performTasks();

    /**
     * @brief stopTasks stops execution of tasks.
     *
     */
    void stopTasks();

    /**
     * @brief addTasks tries adding a task defined in file.
     *
     * @param path path to file.
     */
    void addTasks(QString path);

    /**
     * @brief remove removes task at index from non-scheduled queue.
     *
     * @param taskNum index of task.
     */
    void remove(int taskNum);

    /**
     * @brief unqueue unqueues task at index from scheduled queue.
     *
     * @param taskNum index of task.
     */
    void unqueue(int taskNum);

    /**
     * @brief queue queues task at index from non-scheduled queue.
     *
     * @param taskNum index of task.
     */
    void queue(int taskNum);

    /**
     * @brief getUnqueuedSize returns size of non-scheduled queue.
     *
     * @return size of non-scheduled queue.
     */
    int getUnqueuedSize();

    /**
     * @brief getQueuedSize returns size of scheduled queue.
     *
     * @return size of scheduled queue.
     */
    int getQueuedSize();

public slots:

    /**
     * @brief slot_makeProgress defines behavior when accepting progress signals.
     *
     * @param progress number in percent.
     */
    void slot_makeProgress(int progress) override;

    /**
     * @brief slot_taskUpdated is used to handle changed task states.
     *
     * @param name task name.
     * @param state task state.
     */
    void slot_taskUpdated(QString name, TaskState state);



signals:

    /**
     * @brief sig_taskUpdate signals changed task to observers.
     *
     * @param name task name.
     * @param state task state.
     */
    void sig_taskUpdate(QString name, QString state);

    /**
     * @brief sig_taskAdded signals successfull addition of task to non-scheduled queue.
     *
     * @param name task name.
     */
    void sig_taskAdded(QString name);

    /**
     * @brief sig_progress signals progress of batch processing.
     *
     * @param progress number in percent
     */
    void sig_progress(int progress);

    /**
     * @brief sig_finished signals completion of all tasks.
     *
     */
    void sig_finished();


private:
    QList<Task*> mUnqueuedTasks;
    QList<Task*> mQueuedTasks;
    DataManager *mDataManager;
    QList<Task*>::iterator mRunningTask;

    bool stop = false;
    int tasksCompleted = 0;
};

#endif // AUTOMATOR_H
