#include "flickrsettings.h"
#include "ui_flickrsettings.h"

FlickrSettings::FlickrSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlickrSettings)
{
    ui->setupUi(this);
    loadSettings();
}

FlickrSettings::~FlickrSettings()
{
    delete ui;
}


void FlickrSettings::saveSettings()
{

    QSettings settings("Flickr Plugin",QSettings::IniFormat);
    settings.setValue("API Key",ui->lineEdit_ApiKey->text());
    qDebug() << settings.fileName();
}



void FlickrSettings::loadSettings()
{
    QSettings settings("Flickr Plugin",QSettings::IniFormat);
    ui->lineEdit_ApiKey->setText(settings.value("API Key","Bitte API Key eintragen").toString());
}
