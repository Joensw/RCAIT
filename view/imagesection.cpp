#include "imagesection.h"
#include "ui_imagesection.h"



ImageSection::ImageSection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imagesection)
{
    ui->setupUi(this);

}


ImageSection::~ImageSection()
{
    delete ui;
}

void ImageSection::on_pushButton_clicked()
{

   ui->datasetTrainImages->removeSelected();
   ui->datasetValidationImages->removeSelected();
   ui->newValidationImages->removeSelected();
   ui->newTrainImages->removeSelected();
}

void ImageSection::setCurrentDataSetTrainImages(QMap<QString, QStringList> labelToPathsMap) {
    ImageGalleryTree* newTree = new ImageGalleryTree(labelToPathsMap);
    newTree->setObjectName("datasetTrainImages");
    replaceGalleryTree(ui->datasetTrainImages, newTree);
    ui->datasetTrainImages = newTree;
}

void ImageSection::setCurrentDataSetValidationImages(QMap<QString, QStringList> labelToPathsMap) {
    ImageGalleryTree* newTree = new ImageGalleryTree(labelToPathsMap);
    newTree->setObjectName("datasetValidationImages");
    replaceGalleryTree(ui->datasetValidationImages, newTree);
    ui->datasetValidationImages = newTree;
}

void ImageSection::setNewValidationImages(QMap<QString, QStringList> labelToPathsMap) {
    ImageGalleryTree* newTree = new ImageGalleryTree(labelToPathsMap);
    newTree->setObjectName("newValidationImages");
    replaceGalleryTree(ui->newValidationImages, newTree);
    ui->newValidationImages = newTree;
}

void ImageSection::setNewTrainImages(QMap<QString, QStringList> labelToPathsMap) {
    ImageGalleryTree* newTree = new ImageGalleryTree(labelToPathsMap);
    newTree->setObjectName("newTrainImages");
    replaceGalleryTree(ui->newTrainImages, newTree);
    ui->newTrainImages = newTree;
}

void ImageSection::replaceGalleryTree(ImageGalleryTree *oldGalleryTree, ImageGalleryTree *newGalleryTree) {
    ui->gridLayout->replaceWidget(oldGalleryTree,newGalleryTree);
    delete oldGalleryTree;
    ui->gridLayout->update();
}


void ImageSection::on_pushButton_commit_clicked()
{
    emit sig_mergeDatasets();
}


void ImageSection::on_pushButton_removeImages_clicked()
{
    //ui->datasetTrainImages->test();
    emit sig_removeImages(3,  ui->datasetTrainImages->removeSelected());
    emit sig_removeImages(2,  ui->datasetValidationImages->removeSelected());
    emit sig_removeImages(0,  ui->newValidationImages->removeSelected());
    emit sig_removeImages(1,   ui->newTrainImages->removeSelected());

}

