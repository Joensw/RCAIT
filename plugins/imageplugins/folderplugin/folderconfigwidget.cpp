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
    return ui->comboBox->currentIndex();
}

QString FolderConfigwidget::getImageFolder()
{
    return imageFolder;
}



void FolderConfigwidget::on_loadFolderButton_clicked()
{
    imageFolder = QFileDialog::getExistingDirectory(this, tr("Select image directory"));
    return;
}

