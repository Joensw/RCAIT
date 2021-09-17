/**
 * @file folderwidget.cpp
 *
 * @brief contains method implementations for the FolderWidget class
 */
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
    ui->save_label->clear();
    ui->save_label->setStyleSheet("QLabel { color : green; }");
    ui->save_label->setText(tr("Saved changes."));
    return imageFolder;
}

void FolderConfigwidget::setImageFolder(QString folder)
{
    imageFolder = folder;
}



void FolderConfigwidget::on_loadFolderButton_clicked()
{
    ui->save_label->clear();
    imageFolder = QFileDialog::getExistingDirectory(this, tr("Select image directory"));
    ui->save_label->setStyleSheet("QLabel { color : blue; }");
    ui->save_label->setText(tr("There may be unsaved changes."));
}


void FolderConfigwidget::on_comboBox_currentIndexChanged(int index)
{
    ui->save_label->clear();
    loadMode = index;
    ui->save_label->setStyleSheet("QLabel { color : blue; }");
    ui->save_label->setText(tr("There may be unsaved changes."));
}

void FolderConfigwidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

