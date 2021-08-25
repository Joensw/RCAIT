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
//FIXME: where is an error QMetaObject::connectSlotsByName: No matching signal for on_pushButton_clicked()
void ImageInspectionWidget::on_pushButton_clicked()
{

   ui->datasetTrainImages->removeSelected();
   ui->datasetValidationImages->removeSelected();
   ui->newValidationImages->removeSelected();
   ui->newTrainImages->removeSelected();
}

void ImageInspectionWidget::setCurrentDataSetTrainImages(QMap<QString, QStringList> labelToPathsMap) {
    ui->datasetTrainImages->resetTree();
    ui->datasetTrainImages->addLabels(labelToPathsMap);
}

void ImageInspectionWidget::setCurrentDataSetValidationImages(QMap<QString, QStringList> labelToPathsMap) {
    ui->datasetValidationImages->resetTree();
    ui->datasetValidationImages->addLabels(labelToPathsMap);
}

void ImageInspectionWidget::setNewValidationImages(QMap<QString, QStringList> labelToPathsMap) {
    ui->newValidationImages->resetTree();
    ui->newValidationImages->addLabels(labelToPathsMap);
}

void ImageInspectionWidget::setNewTrainImages(QMap<QString, QStringList> labelToPathsMap) {
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


void ImageInspectionWidget::on_pushButton_removeImages_clicked()
{
    //ui->datasetTrainImages->test();
    emit sig_removeImages(3,  ui->datasetTrainImages->removeSelected());
    emit sig_removeImages(2,  ui->datasetValidationImages->removeSelected());
    emit sig_removeImages(0,  ui->newValidationImages->removeSelected());
    emit sig_removeImages(1,   ui->newTrainImages->removeSelected());

}

