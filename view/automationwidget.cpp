#include "automationwidget.h"
#include "ui_automationwidget.h"

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

void AutomationWidget::on_startButton_clicked()
{
    emit sig_start();
    ui->stopButton->setEnabled(true);
    ui->startButton->setEnabled(false);
}


void AutomationWidget::on_stopButton_clicked()
{
    emit sig_stop();
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
}


void AutomationWidget::on_removeButton_clicked()
{
    for (QModelIndex index : ui->idleTasks->selectionModel()->selectedIndexes()){
        emit sig_remove(index.row());
    }
}


void AutomationWidget::on_unqueueSelectedButton_clicked()
{
    for (QModelIndex index : ui->queuedTasks->selectionModel()->selectedIndexes()){
        emit sig_unqueueSelected(index.row());
    }
}


void AutomationWidget::on_queueSelectedButton_clicked()
{
    for (QModelIndex index : ui->idleTasks->selectionModel()->selectedIndexes()){
        emit sig_queueSelected(index.row());
    }
}


void AutomationWidget::on_queueAllButton_clicked()
{
    int size = ui->idleTasks->count();

    for (int i = 0; i < size; i++){
        ui->queuedTasks->addItem(ui->idleTasks->item(i)->text());
        ui->idleTasks->removeItemWidget(ui->idleTasks->item(i));
    }
}


void AutomationWidget::on_unqueueAllButton_clicked()
{
    int size = ui->queuedTasks->count();

    for (int i = 0; i < size; i++){
        ui->idleTasks->addItem(ui->queuedTasks->item(i)->text());
        ui->queuedTasks->removeItemWidget(ui->idleTasks->item(i));
    }
}

