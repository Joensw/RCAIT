#ifndef AUTOMATIONWIDGET_H
#define AUTOMATIONWIDGET_H

#include <QWidget>

namespace Ui {
class AutomationWidget;
}

class AutomationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AutomationWidget(QWidget *parent = nullptr);
    ~AutomationWidget();

    void addTask(QString name);

public slots:
    void slot_progress(int progress);
    void slot_taskUpdate(QString name, QString state);


signals:
    void sig_start();
    void sig_stop();
    void sig_remove(int index);
    void sig_import(QString path);
    void sig_queueAll();
    void sig_unqueueAll();
    void sig_queueSelected(int index);
    void sig_unqueueSelected(int index);


private slots:
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_removeButton_clicked();

    void on_unqueueSelectedButton_clicked();

    void on_queueSelectedButton_clicked();

    void on_queueAllButton_clicked();

    void on_unqueueAllButton_clicked();

    void on_importTasksButton_clicked();

private:
    Ui::AutomationWidget *ui;
};

#endif // AUTOMATIONWIDGET_H
