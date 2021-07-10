#include "aitrainingwidget.h"
#include "ui_aitrainingwidget.h"

#include <QDoubleValidator>
#include <QPair>

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

int AITrainingWidget::getCropSize()
{
    return ui->resizedCropSize->value();
}

QString AITrainingWidget::getFlipDirection()
{
    return ui->flipDirection->text();
}

double AITrainingWidget::getFlipProbability()
{
    return ui->flipProbability->value();
}

QVector<QPair<double, double>> AITrainingWidget::getNormalizationTable()
{
    QVector<QPair<double, double>> normalizationTable(3, QPair<double, double>(ui->red_mean->value(), ui->red_std->value()));
    normalizationTable.append(QPair<double, double>(ui->green_mean->value(), ui->green_std->value()));
    normalizationTable.append(QPair<double, double>(ui->blue_mean->value(), ui->blue_std->value()));
    return normalizationTable;
}

int AITrainingWidget::getResizeValue()
{
    return ui->resize->value();
}

void AITrainingWidget::on_previewButton_clicked()
{
    emit sig_showAugmentationPreview();
}

void AITrainingWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is send if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

