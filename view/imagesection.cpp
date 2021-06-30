#include "imagesection.h"
#include "ui_imagesection.h"
#include "imagegallerytree.h"


const QStringList inputImagePath = {":/Resources/images/Flugzeug/", ":/Resources/images/Truck/" , ":/Resources/images/Auto"};
const QStringList trainingImagePath = {":/Resources/images/Flugzeug/", ":/Resources/images/Truck/", ":/Resources/images/Auto"};

//Test Konstruktor, der immer die obigen Strings als Pfad wählt
ImageSection::ImageSection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imagesection)
{
    ui->setupUi(this);



    ui->inputImages = new ImageGalleryTree(inputImagePath);
    ui->gridLayout->addWidget(ui->inputImages, 1, 0, 1, 1);
    ui->gridLayout->update();

     ui->trainingImages = new ImageGalleryTree(trainingImagePath );
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

