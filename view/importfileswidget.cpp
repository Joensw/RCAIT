//
// Created by Paul on 02.07.2021.
//

#include "importfileswidget.h"
#include "ui_importfileswidget.h"

ImportFilesWidget::ImportFilesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImportFilesWidget)
{
    ui->setupUi(this);
}

ImportFilesWidget::~ImportFilesWidget()
{
    delete ui;
}

void ImportFilesWidget::on_pushButton_clearTags_clicked() {
    std::vector<QString> tags;
    ui->lineEdit_labels->tags(tags);
}
