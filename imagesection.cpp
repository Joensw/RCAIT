#include "imagesection.h"
#include "ui_imagesection.h"


const QString inputImagePath = "D:\\Benutzer\\Paul\\Bilder\\GoogleImagesDownloader-urllib-downloader\\GoogleImagesDownloader-urllib-downloader\\urllib_downloader\\Example\\data\\Car";
const QString trainingImagePath = "D:\\Benutzer\\Paul\\Bilder\\GoogleImagesDownloader-urllib-downloader\\GoogleImagesDownloader-urllib-downloader\\urllib_downloader\\Example\\data\\Truck";


ImageSection::ImageSection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::imagesection)
{
    ui->setupUi(this);



    ui->inputImages = startGallery(inputImagePath);
    ui->gridLayout->addWidget(ui->inputImages, 1, 0, 1, 1);
    ui->gridLayout->update();

     ui->trainingImages = startGallery(trainingImagePath);
     ui->gridLayout->addWidget(ui->trainingImages, 1, 1, 1, 1);
     ui->gridLayout->update();

}


ImageSection::ImageSection(QWidget *parent, QString inputPath, QString trainingPath) :
    QWidget(parent),
    ui(new Ui::imagesection)
{
    ui->setupUi(this);



    ui->inputImages = startGallery(inputPath);
    ui->gridLayout->addWidget(ui->inputImages, 1, 0, 1, 1);
    ui->gridLayout->update();

     ui->trainingImages = startGallery(trainingPath);
     ui->gridLayout->addWidget(ui->trainingImages, 1, 1, 1, 1);
     ui->gridLayout->update();

}



ImageGallery* ImageSection::startGallery( QString path)
{
    QFileInfo info(path);

    if(!info.exists()){
        return NULL;
    }

    if (info.isDir()){
        return new ImageGallery(this, QDir(path));
    } else {
        return new ImageGallery(this, path);
    }
}

ImageSection::~ImageSection()
{
    delete ui;
}

void ImageSection::on_pushButton_clicked()
{
    ui->trainingImages->removeselected();
}

