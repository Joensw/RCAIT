#ifndef AUTOMATIONCONTROLLER_H
#define AUTOMATIONCONTROLLER_H

#include <datamanager.h>
#include <QObject>
#include <automationwidget.h>
#include <automator.h>

/**
 * @brief The AutomationController class mediates between ui elements and the batch processing of tasks.
 *
 */
class AutomationController : public QObject
{
    Q_OBJECT
public:

    /**
     * @brief AutomationController constructs an AutomationController.
     *
     * @param dataManager source of general information.
     * @param automationWidget user interface for operating automation.
     */
    AutomationController(DataManager *dataManager, AutomationWidget *automationWidget);

public slots:

    /**
     * @brief slot_start starts execution of tasks.
     *
     */
    void slot_start();

    /**
     * @brief slot_stop stops exection of tasks.
     *
     */
    void slot_stop();

    /**
     * @brief slot_remove removes task at index.
     *
     * @param index index of task.
     */
    void slot_remove(int index);

    /**
     * @brief slot_import tries to import task defined in file.
     *
     * @param path path to file.
     */
    void slot_import(QString path);

    /**
     * @brief slot_queueAll queues all tasks for execution.
     *
     */
    void slot_queueAll();

    /**
     * @brief slot_unqueueAll unqueues all tasks.
     */
    void slot_unqueueAll();

    /**
     * @brief slot_queueSelected queues task at index for execution.
     *
     * @param index index of task.
     */
    void slot_queueSelected(int index);

    /**
     * @brief slot_unqueueSelected  unqueues task at index.
     *
     * @param index index of task.
     */
    void slot_unqueueSelected(int index);

private:
    AutomationWidget *mWidget;
    DataManager *mDataManager;
    Automator* mAutomator;

};

#endif // AUTOMATIONCONTROLLER_H
