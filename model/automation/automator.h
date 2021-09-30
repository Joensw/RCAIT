#ifndef AUTOMATOR_H
#define AUTOMATOR_H

#include "task.h"
#include <datamanager.h>
#include <pluginusage/progressable.h>
#include <QJsonDocument>


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
    Automator();

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
    void addTasks(const QString &path);

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
    qsizetype getUnqueuedSize() const;

    /**
     * @brief getQueuedSize returns size of scheduled queue.
     *
     * @return size of scheduled queue.
     */
    qsizetype getQueuedSize() const;

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
     * @param taskName task name.
     * @param state task state.
     */
    void slot_taskUpdated(const QString &taskName, TaskState state);



signals:

    /**
     * @brief sig_taskUpdate signals changed task to observers.
     *
     * @param name task name.
     * @param state task state.
     */
    void sig_taskUpdate(QString name, QString state);

    /**
     * @brief sig_taskAdded signals successful addition of task to non-scheduled queue.
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

    /**
     * @brief sig_trainingResultUpdated signals new training result from automation.
     *
     * @param result training result
     */
    void sig_trainingResultUpdated(const QSharedPointer<TrainingResult> & result);

    /**
     * @brief sig_classificationResultUpdated signals new classification result from automation.
     *
     * @param result classification result
     */
    void sig_classificationResultUpdated(const QSharedPointer<ClassificationResult> & result);

    /**
     * @brief sig_projectCreated signals potential creation of new project.
     *
     */
    void sig_projectCreated();


private:
    QList<QSharedPointer<Task>> mUnqueuedTasks;
    QList<QSharedPointer<Task>> mQueuedTasks;
    QList<QSharedPointer<Task>>::iterator mRunningTask;

    bool stop = false;
    int tasksCompleted = 0;
};

#endif // AUTOMATOR_H
