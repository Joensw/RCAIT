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
    for (QModelIndex index : ui->idleTasks->selectionModel()->selectedIndexes()){
        emit sig_remove(index.row());
    }
    qDeleteAll(ui->idleTasks->selectedItems());
}


void AutomationWidget::on_unqueueSelectedButton_clicked()
{
    for (QModelIndex index : ui->queuedTasks->selectionModel()->selectedIndexes()){
        ui->idleTasks->addItem(ui->queuedTasks->takeItem(index.row()));
        emit sig_unqueueSelected(index.row());
    }
    qDeleteAll(ui->queuedTasks->selectedItems());
}


void AutomationWidget::on_queueSelectedButton_clicked()
{
    for (QModelIndex index : ui->idleTasks->selectionModel()->selectedIndexes()){
        ui->queuedTasks->addItem(ui->idleTasks->takeItem(index.row()));
        emit sig_queueSelected(index.row());
    }
    qDeleteAll(ui->idleTasks->selectedItems());
}


void AutomationWidget::on_queueAllButton_clicked()
{
    int size = ui->idleTasks->count();

    for (int i = size - 1; i >= 0; i--){
        ui->queuedTasks->addItem(ui->idleTasks->takeItem(i));
    }
    emit sig_queueAll();
}


void AutomationWidget::on_unqueueAllButton_clicked()
{
    int size = ui->queuedTasks->count();

    for (int i = size - 1; i >= 0; i--){
        ui->idleTasks->addItem(ui->queuedTasks->takeItem(i));
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

