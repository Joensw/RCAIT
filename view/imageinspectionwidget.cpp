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

void ImageInspectionWidget::on_pushButton_clicked()
{

   ui->datasetTrainImages->removeSelected();
   ui->datasetValidationImages->removeSelected();
   ui->newValidationImages->removeSelected();
   ui->newTrainImages->removeSelected();
}

void ImageInspectionWidget::setCurrentDataSetTrainImages(QMap<QString, QStringList> labelToPathsMap) {
    ImageGalleryTree* newTree = new ImageGalleryTree(labelToPathsMap);
    newTree->setObjectName("datasetTrainImages");
    replaceGalleryTree(ui->datasetTrainImages, newTree);
    ui->datasetTrainImages = newTree;
}

void ImageInspectionWidget::setCurrentDataSetValidationImages(QMap<QString, QStringList> labelToPathsMap) {
    ImageGalleryTree* newTree = new ImageGalleryTree(labelToPathsMap);
    newTree->setObjectName("datasetValidationImages");
    replaceGalleryTree(ui->datasetValidationImages, newTree);
    ui->datasetValidationImages = newTree;
}

void ImageInspectionWidget::setNewValidationImages(QMap<QString, QStringList> labelToPathsMap) {
    ImageGalleryTree* newTree = new ImageGalleryTree(labelToPathsMap);
    newTree->setObjectName("newValidationImages");
    replaceGalleryTree(ui->newValidationImages, newTree);
    ui->newValidationImages = newTree;
}

void ImageInspectionWidget::setNewTrainImages(QMap<QString, QStringList> labelToPathsMap) {
    ImageGalleryTree* newTree = new ImageGalleryTree(labelToPathsMap);
    newTree->setObjectName("newTrainImages");
    replaceGalleryTree(ui->newTrainImages, newTree);
    ui->newTrainImages = newTree;
}

void ImageInspectionWidget::replaceGalleryTree(ImageGalleryTree *oldGalleryTree, ImageGalleryTree *newGalleryTree) {
    ui->gridLayout->replaceWidget(oldGalleryTree,newGalleryTree);
    delete oldGalleryTree;
    ui->gridLayout->update();
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

