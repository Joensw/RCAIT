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
    ui->label_splitPercent->setText(QString::number(ui->horizontalSlider->value())+"%");


}

ImportFilesWidget::~ImportFilesWidget()
{
    delete ui;
}

void ImportFilesWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is send if a translator is loaded
        retranslateUi();
        ui->retranslateUi(this);
    }
    //Call to parent class
    QWidget::changeEvent(event);
}

/**
 * Translate and set all the strings which
 * were not created in the UI builder
 */
void ImportFilesWidget::retranslateUi() {

}


void ImportFilesWidget::on_pushButton_clearTags_clicked() {
    std::vector<QString> tags;
    ui->lineEdit_labels->tags(tags);
}

void ImportFilesWidget::on_pushButton_addModel_clicked()
{
    emit sig_newModel();
}

void ImportFilesWidget::on_pushButton_removeModel_clicked()
{
    //if there are no projects, or no current item, dont do anything
    QListWidgetItem * item = ui->listWidget_modelNames->currentItem();
    if (item) {
        QString toRemove = item->text();
        emit sig_removeModel(toRemove);
    }
}

void ImportFilesWidget::on_pushButton_loadModel_clicked()
{
    QListWidgetItem * item = ui->listWidget_modelNames->currentItem();
    if (item) {
        QString toLoad = item->text();
        emit sig_loadModel(toLoad);
    }
}




void ImportFilesWidget::on_pushButton_loadImages_clicked()
{
    std::vector<QString> labelsVector =  ui->lineEdit_labels->tags();
    QStringList labelsList;
    for( QString label : labelsVector){
        labelsList.append(label);
    }

    emit sig_loadInputImages( ui->comboBox_plugins->currentText(),ui->spinBox_amount->value(),labelsList,ui->horizontalSlider->value());

}

void ImportFilesWidget::setAvailablePlugins(QStringList pluginNames) {
    ui->comboBox_plugins->clear();
    ui->comboBox_plugins->addItems(pluginNames);
}





void ImportFilesWidget::on_horizontalSlider_sliderMoved(int position)
{
     ui->label_splitPercent->setText(QString::number(position)+"%");
}


