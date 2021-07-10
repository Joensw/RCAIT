#include "automationwidget.h"
#include "ui_automationwidget.h"

#include <QFileDialog>

AutomationWidget::AutomationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutomationWidget)
{
    ui->setupUi(this);
}

AutomationWidget::~AutomationWidget()
{
    delete ui;
}

void AutomationWidget::addTask(QString name)
{
    ui->idleTasks->addItem(name);
}

void AutomationWidget::slot_taskUpdate(QString name, QString state)
{
    QList<QListWidgetItem*> task = ui->queuedTasks->findItems(name, Qt::MatchExactly);
    //icons have to be named after states
    task.at(0)->setIcon(QIcon(":/Resources/TaskIcons/" + state + ".svg"));
}

void AutomationWidget::on_startButton_clicked()
{
    emit sig_start();
    ui->stopButton->setEnabled(true);
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
        emit sig_unqueueSelected(index.row());
        ui->idleTasks->addItem(ui->queuedTasks->item(index.row())->text());
    }
    qDeleteAll(ui->queuedTasks->selectedItems());
}


void AutomationWidget::on_queueSelectedButton_clicked()
{
    for (QModelIndex index : ui->idleTasks->selectionModel()->selectedIndexes()){
        emit sig_queueSelected(index.row());
        ui->queuedTasks->addItem(ui->idleTasks->item(index.row())->text());
    }
    qDeleteAll(ui->idleTasks->selectedItems());
}


void AutomationWidget::on_queueAllButton_clicked()
{
    emit sig_queueAll();

    int size = ui->idleTasks->count();

    for (int i = size - 1; i >= 0; i--){
        ui->queuedTasks->addItem(ui->idleTasks->item(i)->text());
        ui->idleTasks->removeItemWidget(ui->idleTasks->item(i));
    }
}


void AutomationWidget::on_unqueueAllButton_clicked()
{
    emit sig_unqueueAll();

    int size = ui->queuedTasks->count();

    for (int i = size - 1; i >= 0; i--){
        ui->idleTasks->addItem(ui->queuedTasks->item(i)->text());
        ui->queuedTasks->removeItemWidget(ui->idleTasks->item(i));
    }
}


void AutomationWidget::on_importTasksButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, QString(), QString(), "*.json");
    if (path == nullptr) return;
    emit sig_import(path);
}

