#ifndef AUTOMATIONWIDGET_H
#define AUTOMATIONWIDGET_H

#include <QWidget>
#include <QFileDialog>
#include <QScroller>

namespace Ui {
class AutomationWidget;
}

/**
 * @brief The AutomationWidget class acts as the ui to the batch processing functionality.
 *
 */
class AutomationWidget : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief AutomationWidget constructs a new AutomationWidget with optional parent parameter.
     * @param parent parent widget.
     */
    explicit AutomationWidget(QWidget *parent = nullptr);

    /**
     * @brief destructor
     */
    ~AutomationWidget() override;



public slots:

    /**
     * @brief slot_progress is used to update progressbar on progress.
     *
     * @param progress number in percent.
     */
    void slot_progress(const int &progress);

    /**
     * @brief slot_taskAdded is used to add a task to the idle list.
     *
     * @param name name of the task.
     */
    void slot_taskAdded(const QString &name);

    /**
     * @brief slot_taskUpdate is used change the task status icon on status change.
     *
     * @param name name of the task.
     * @param state new state of task.
     */
    void slot_taskUpdate(const QString &name, const QString &state) const;

    /**
     * @brief slot_finished resets most buttons/elements to pre-start state.
     *
     */
    void slot_finished();

signals:

    /**
     * @brief sig_start signals the start of task execution.
     *
     */
    void sig_start();

    /**
     * @brief sig_stop signals stopping of task execution.
     *
     */
    void sig_stop();

    /**
     * @brief sig_remove signals removal of task at index.
     *
     * @param index index of task to be removed.
     */
    void sig_remove(int index);

    /**
     * @brief sig_import signals import of task in specified file.
     *
     * @param path path to file containing task.
     */
    void sig_import(QString path);

    /**
     * @brief sig_queueAll signals moving all tasks to execution queue.
     *
     */
    void sig_queueAll();

    /**
     * @brief sig_unqueueAll signals moving all tasks to queue of idle tasks.
     *
     */
    void sig_unqueueAll();

    /**
     * @brief sig_queueSelected signals moving task at index to execution queue.
     *
     * @param index index of task.
     */
    void sig_queueSelected(int index);

    /**
     * @brief sig_unqueueSelected signals moving task at index to queue of idle tasks.
     *
     * @param index index of task.
     */
    void sig_unqueueSelected(int index);


protected:

    /**
     * @brief changeEvent event handler
     *
     * @param event incoming event
     */
    void changeEvent(QEvent *event) override;

private slots:
    [[maybe_unused]] void on_startButton_clicked();

    [[maybe_unused]] void on_stopButton_clicked();

    [[maybe_unused]] void on_removeButton_clicked();

    [[maybe_unused]] void on_unqueueSelectedButton_clicked();

    [[maybe_unused]] void on_queueSelectedButton_clicked();

    [[maybe_unused]] void on_queueAllButton_clicked();

    [[maybe_unused]] void on_unqueueAllButton_clicked();

    [[maybe_unused]] void on_importTasksButton_clicked();

private:
    static constexpr auto TASK_NONSCHEDULED_ICON = ":/TaskIcons/Not_Scheduled.svg";
    static constexpr auto GENERIC_TASK_ICON = ":/TaskIcons/%1.svg";

    Ui::AutomationWidget *ui;
};

#endif // AUTOMATIONWIDGET_H
