#include "aitrainingwidget.h"
#include "ui_aitrainingwidget.h"


AITrainingWidget::AITrainingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AITrainingWidget)
{
    ui->setupUi(this);
    ui->tab_aitraining->setTabEnabled(1, false);
}

AITrainingWidget::~AITrainingWidget()
{
    delete ui;
}

void AITrainingWidget::slot_progress(const int &progress)
{
    ui->progressBar->setValue(progress);
}

[[maybe_unused]] void AITrainingWidget::on_startButton_clicked()
{
    emit sig_startTraining();
    ui->progressBar->setEnabled(true);
}


void AITrainingWidget::setDataAugWidget(const QSharedPointer<QWidget> &replacement) {
    ui->scrollArea_augmentation->setWidget(&*replacement);
}

void AITrainingWidget::setAIConfigWidget(const QSharedPointer<QWidget> &replacement) {
    ui->scrollArea_configuration->setWidget(&*replacement);
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

void AITrainingWidget::showImages(const QString& path){
    ui->tab_aitraining->setTabEnabled(1, true);
    ui->tab_preview->clearAndStop();
    ui->tab_preview->setEnabled(true);
    ui->tab_preview->concurrentAddImages(path);
}

