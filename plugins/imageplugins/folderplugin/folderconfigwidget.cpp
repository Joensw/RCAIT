#include "folderconfigwidget.h"
#include "ui_folderconfigwidget.h"

#include <QtWidgets/QFileDialog>

FolderConfigwidget::FolderConfigwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FolderConfigwidget)
{
    ui->setupUi(this);
}

FolderConfigwidget::~FolderConfigwidget()
{
    delete ui;
}

int FolderConfigwidget::getLoadMode()
{
    return loadMode;
}

void FolderConfigwidget::setLoadMode(int mode)
{
    loadMode = mode;
}

QString FolderConfigwidget::getImageFolder()
{
    return imageFolder;
}

void FolderConfigwidget::setImageFolder(QString folder)
{
    imageFolder = folder;
}



void FolderConfigwidget::on_loadFolderButton_clicked()
{
    imageFolder = QFileDialog::getExistingDirectory(this, tr("Select image directory"));
    return;
}


void FolderConfigwidget::on_comboBox_currentIndexChanged(int index)
{
    loadMode = index;
}

