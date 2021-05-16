#include "imagesection.h"
#include "ui_imagesection.h"
#include "imagegallerytree.h"


const QString inputImagePath = "D:/Bilder/Platzhaltzer/";
const QString trainingImagePath = "D:/Bilder/Auto/";

//Test Konstruktor, der immer die obigen Strings als Pfad wählt
ImageSection::ImageSection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imagesection)
{
    ui->setupUi(this);



    ui->inputImages = new ImageGalleryTree(QStringList() << inputImagePath << "D:/Bilder/test_1" << "D:/Bilder/Körperwelten");
    ui->gridLayout->addWidget(ui->inputImages, 1, 0, 1, 1);
    ui->gridLayout->update();

     ui->trainingImages = new ImageGalleryTree(QStringList() << trainingImagePath );
     ui->gridLayout->addWidget(ui->trainingImages, 1, 1, 1, 1);
     ui->gridLayout->update();

}


//tatsächlicher Konstruktor
ImageSection::ImageSection(QWidget *parent, QStringList inputPath, QStringList trainingPath) :
    QWidget(parent),
    ui(new Ui::imagesection)
{
    ui->setupUi(this);



    ui->inputImages = new ImageGalleryTree(inputPath);
    ui->gridLayout->addWidget(ui->inputImages, 1, 0, 1, 1);
    ui->gridLayout->update();

     ui->trainingImages = new ImageGalleryTree(trainingPath);
     ui->gridLayout->addWidget(ui->trainingImages, 1, 1, 1, 1);
     ui->gridLayout->update();
}




ImageSection::~ImageSection()
{
    delete ui;
}

void ImageSection::on_pushButton_clicked()
{
   ui->trainingImages->removeSelected();
}

