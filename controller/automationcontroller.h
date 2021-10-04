/**
 * @file automationcontroller.h
 *
 * @brief connects the automation interface with the automation logic
 *
 * @author Adrian Nelson
 */
#ifndef AUTOMATIONCONTROLLER_H
#define AUTOMATIONCONTROLLER_H

#include <datamanager.h>
#include <QObject>
#include <QtConcurrent/QtConcurrent>
#include <utility>
#include <automationwidget.h>
#include <automator.h>

/**
 * @brief The AutomationController class mediates between ui elements and the batch processing of tasks.
 *
 */
class AutomationController final : public QObject {
Q_OBJECT
public:

    /**
     * @brief AutomationController constructs an AutomationController.
     *
     * @param dataManager source of general information.
     * @param automationWidget user interface for operating automation.
     */
    AutomationController(AutomationWidget *automationWidget);

    /**
     * @brief operator = deleted assignment operator
     */
    AutomationController &operator=(const AutomationController &) = delete;

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
     * @brief slot_unqueueSelected unqueues task at index.
     *
     * @param index index of task.
     */
    void slot_unqueueSelected(int index);

signals:
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

    /**
     * @brief slot_projectCreated used to signal update of project directory.
     */
    void sig_projectDirectoryChanged();

private:
    AutomationWidget *mWidget;
    QScopedPointer<Automator> mAutomator;

};

#endif // AUTOMATIONCONTROLLER_H
