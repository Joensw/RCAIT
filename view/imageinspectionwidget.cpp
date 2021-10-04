/**
 *@file imageinspectionwidget.cpp
 *
 *@brief contains method implementations for ImageInspectionWidget class
 */
#include "imageinspectionwidget.h"
#include "ui_imageinspectionwidget.h"



ImageInspectionWidget::ImageInspectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageInspectionWidget)
{
    ui->setupUi(this);

}


ImageInspectionWidget::~ImageInspectionWidget()
{
    delete ui;
}

void ImageInspectionWidget::setCurrentDataSetTrainImages(const QMap<QString, QStringList> &labelToPathsMap) {
    ui->datasetTrainImages->resetTree();
    ui->datasetTrainImages->addLabels(labelToPathsMap);
}

void ImageInspectionWidget::setCurrentDataSetValidationImages(const QMap<QString, QStringList> &labelToPathsMap) {
    ui->datasetValidationImages->resetTree();
    ui->datasetValidationImages->addLabels(labelToPathsMap);
}

void ImageInspectionWidget::setNewValidationImages(const QMap<QString, QStringList> &labelToPathsMap) {
    ui->newValidationImages->resetTree();
    ui->newValidationImages->addLabels(labelToPathsMap);
}

void ImageInspectionWidget::setNewTrainImages(const QMap<QString, QStringList> &labelToPathsMap) {
    ui->newTrainImages->resetTree();
    ui->newTrainImages->addLabels(labelToPathsMap);
}

void ImageInspectionWidget::slot_imagesUpdated()
{
    ui->pushButton_commit->setEnabled(true);
}

void ImageInspectionWidget::slot_startLoading()
{
    ui->pushButton_commit->setEnabled(false);
}


void ImageInspectionWidget::on_pushButton_commit_clicked()
{
    emit sig_mergeDatasets();
}


void ImageInspectionWidget::on_pushButton_removeImages_clicked() {
    emit sig_removeImages(3, ui->datasetTrainImages->removeSelected());
    emit sig_removeImages(2, ui->datasetValidationImages->removeSelected());
    emit sig_removeImages(0, ui->newValidationImages->removeSelected());
    emit sig_removeImages(1, ui->newTrainImages->removeSelected());
}

void ImageInspectionWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

void ImageInspectionWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Delete){
        this->on_pushButton_removeImages_clicked();
    }

    QWidget::keyPressEvent(event);
}

