#include "automationwidget.h"
#include "ui_automationwidget.h"

#include <QFileDialog>
#include <QScroller>

AutomationWidget::AutomationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutomationWidget)
{
    ui->setupUi(this);

    // Add full touch compliance
    QScroller::grabGesture(ui->idleTasks, QScroller::TouchGesture);
    QScroller::grabGesture(ui->queuedTasks, QScroller::TouchGesture);

}

AutomationWidget::~AutomationWidget()
{
    delete ui;
}

void AutomationWidget::slot_progress(int progress)
{
    ui->progressBar->setValue(progress);
}

void AutomationWidget::slot_finished()
{
    ui->progressBar->setValue(100);
    ui->startButton->setEnabled(true);
    ui->queueAllButton->setEnabled(true);
    ui->unqueueAllButton->setEnabled(true);
    ui->queueSelectedButton->setEnabled(true);
    ui->unqueueSelectedButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->progressBar->setEnabled(false);
}



void AutomationWidget::slot_taskAdded(QString name)
{
    ui->idleTasks->addItem(name);
}

void AutomationWidget::slot_taskUpdate(QString name, QString state)
{
    if (state == "Not_Scheduled"){
         ui->idleTasks->findItems(name, Qt::MatchExactly).at(0)->setIcon(QIcon(":/Resources/TaskIcons/Not_Scheduled.svg"));
         return;
    }
    QList<QListWidgetItem*> task = ui->queuedTasks->findItems(name, Qt::MatchExactly);
    //icons have to be named after states
    task.at(0)->setIcon(QIcon(":/Resources/TaskIcons/" + state + ".svg"));
}

void AutomationWidget::on_startButton_clicked()
{
    emit sig_start();
    ui->stopButton->setEnabled(true);
    ui->progressBar->setEnabled(true);
    ui->startButton->setEnabled(false);
    ui->queueAllButton->setEnabled(false);
    ui->unqueueAllButton->setEnabled(false);
    ui->queueSelectedButton->setEnabled(false);
    ui->unqueueSelectedButton->setEnabled(false);
}


void AutomationWidget::on_stopButton_clicked()
{
    emit sig_stop();
    ui->startButton->setEnabled(true);
    ui->queueAllButton->setEnabled(true);
    ui->unqueueAllButton->setEnabled(true);
    ui->queueSelectedButton->setEnabled(true);
    ui->unqueueSelectedButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->progressBar->setEnabled(false);
}


void AutomationWidget::on_removeButton_clicked()
{
    int size = ui->idleTasks->count();

    for (int i = 0; i < size; i++){
        if (ui->idleTasks->item(i)->isSelected()) {
            ui->idleTasks->takeItem(i);
            emit sig_remove(i);
            i--;
            size--;
        }
    }
}


void AutomationWidget::on_unqueueSelectedButton_clicked()
{
    int size = ui->queuedTasks->count();

    for (int i = 0; i < size; i++){
        if (ui->queuedTasks->item(i)->isSelected()) {
            ui->idleTasks->addItem(ui->queuedTasks->takeItem(i));
            emit sig_unqueueSelected(i);
            i--;
            size--;
        }
    }
}


void AutomationWidget::on_queueSelectedButton_clicked()
{
    int size = ui->idleTasks->count();

    for (int i = 0; i < size; i++){
        if (ui->idleTasks->item(i)->isSelected()) {
            ui->queuedTasks->addItem(ui->idleTasks->takeItem(i));
            emit sig_queueSelected(i);
            i--;
            size--;
        }
    }
}


void AutomationWidget::on_queueAllButton_clicked()
{
    int size = ui->idleTasks->count();

    for (int i = 0; i < size; i++){
        ui->queuedTasks->addItem(ui->idleTasks->takeItem(0));
    }
    emit sig_queueAll();
}


void AutomationWidget::on_unqueueAllButton_clicked()
{
    int size = ui->queuedTasks->count();

    for (int i = 0; i < size; i++){
        ui->idleTasks->addItem(ui->queuedTasks->takeItem(0));
    }
    emit sig_unqueueAll();
}


void AutomationWidget::on_importTasksButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, QString(), QString(), "*.json");
    if (path == nullptr) return;
    emit sig_import(path);
}

void AutomationWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

