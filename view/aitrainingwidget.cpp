#include "aitrainingwidget.h"
#include "ui_aitrainingwidget.h"


AITrainingWidget::AITrainingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AITrainingWidget)
{
    ui->setupUi(this);
}

AITrainingWidget::~AITrainingWidget()
{
    delete ui;
}

void AITrainingWidget::slot_progress(int progress)
{
    ui->progressBar->setValue(progress);
    if (progress == 100){
        ui->resultsButton->setEnabled(true);
    }
}

void AITrainingWidget::on_startButton_clicked()
{
    emit sig_startTraining();
    ui->cancelButton->setEnabled(true);
    ui->progressBar->setEnabled(true);
    ui->startButton->setEnabled(false);
}


void AITrainingWidget::on_cancelButton_clicked()
{
    emit sig_abortTraining();
    ui->startButton->setEnabled(true);
    ui->cancelButton->setEnabled(false);
}


void AITrainingWidget::on_resultsButton_clicked()
{
    emit sig_results();
}

void AITrainingWidget::setDataAugWidget(QWidget *replacement)
{
    //ui->gridLayout_dataAug->replaceWidget(ui->dataAugWidget, replacement);
    ui->scrollArea_augmentation->setWidget(replacement);
}

void AITrainingWidget::setAIConfigWidget(QWidget *replacement)
{
    //ui->gridLayout_AIconfig->replaceWidget(ui->AIConfigWidget, replacement);
    ui->scrollArea_configuration->setWidget(replacement);
}

void AITrainingWidget::on_previewButton_clicked()
{
    emit sig_showAugmentationPreview(ui->spinBox_amount->value());
}

void AITrainingWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

