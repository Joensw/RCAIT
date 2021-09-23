/**
 *@file importfileswidget.cpp
 *
 *@brief contains method implementations for ImportFilesWidget class
 */

#include "importfileswidget.h"
#include "ui_importfileswidget.h"

ImportFilesWidget::ImportFilesWidget(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::ImportFilesWidget) {
    ui->setupUi(this);
    ui->label_splitPercent->setText(QString::number(ui->horizontalSlider->value()) % "%");

}

ImportFilesWidget::~ImportFilesWidget() {
    delete ui;
}

void ImportFilesWidget::changeEvent(QEvent *event) {
    if (event->type() == QEvent::LanguageChange) {
        // this event is sent if a translator is loaded
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

void ImportFilesWidget::addModels(const QStringList &modelNames) {
    ui->listWidget_modelNames->addItems(modelNames);
}

void ImportFilesWidget::addNewModel(const QString &modelName) {
    ui->listWidget_modelNames->addItem(modelName);
}

void ImportFilesWidget::clearModelList() {
    ui->listWidget_modelNames->clear();
}

[[maybe_unused]] void ImportFilesWidget::on_pushButton_clearTags_clicked() {
    ui->lineEdit_labels->tags({});
}

[[maybe_unused]] void ImportFilesWidget::on_pushButton_addModel_clicked() {
    emit sig_newModel();
}

[[maybe_unused]] void ImportFilesWidget::on_pushButton_removeModel_clicked() {
    QListWidgetItem *item = ui->listWidget_modelNames->currentItem();
    if (item) {
        QString toRemove = item->text();
        emit sig_removeModel(toRemove);
    }
}

[[maybe_unused]] void ImportFilesWidget::on_pushButton_loadModel_clicked() {
    QListWidgetItem *item = ui->listWidget_modelNames->currentItem();
    if (item) {
        QString toLoad = item->text();
        emit sig_loadModel(toLoad);
    }
}


[[maybe_unused]] void ImportFilesWidget::on_pushButton_loadImages_clicked() {
    ui->pushButton_loadImages->setEnabled(false);
    ui->pushButton_abortLoading->setEnabled(true);

    std::vector<QString> labelsVector = ui->lineEdit_labels->tags();
    QStringList labelsList;
    for (const QString &label: labelsVector) labelsList << label;

    emit sig_loadInputImages(ui->comboBox_plugins->currentText(), ui->spinBox_amount->value(),
                             labelsList, ui->horizontalSlider->value());

}

void ImportFilesWidget::setAvailablePlugins(const QStringList &pluginNames) {
    ui->comboBox_plugins->clear();
    ui->comboBox_plugins->addItems(pluginNames);
}

void ImportFilesWidget::updateProgressBar(int progress) {
    ui->progressBar_images->setValue(progress);
    if (progress == ui->progressBar_images->maximum()) {
        ui->pushButton_loadImages->setEnabled(true);
        ui->pushButton_abortLoading->setEnabled(false);
    }
}

void ImportFilesWidget::updateStatusText(const QString &status) {
    QFont labelFont = ui->label_pluginStatus->font();
    QFontMetricsF labelFontMetrics(labelFont);
    ui->label_pluginStatus->setText(
            labelFontMetrics.elidedText(status, Qt::TextElideMode::ElideRight, ui->label_pluginStatus->width()));
}


void ImportFilesWidget::on_horizontalSlider_valueChanged(int value) {
    ui->label_splitPercent->setText(QString::number(value) % "%");
}

[[maybe_unused]] void ImportFilesWidget::on_pushButton_loadLabelsFromFile_clicked() {
    QString path = QFileDialog::getOpenFileName(this, DIALOG_CAPTION, "", "*.txt");

    if (path.isEmpty()) return;

    QFile inputFile(path);
    inputFile.open(QIODevice::ReadOnly);

    if (!inputFile.isOpen()) return;
    QTextStream stream(&inputFile);

    std::vector<QString> labelsVector;
    for (auto line = stream.readLine(); !line.isNull(); line = stream.readLine()) {
        //Ignore empty and commented out lines
        if (line.isEmpty() || line.startsWith('#')) continue;
        labelsVector.push_back(line.simplified());
    }

    ui->lineEdit_labels->tags(labelsVector);
}


[[maybe_unused]] void ImportFilesWidget::on_pushButton_abortLoading_clicked() {
    emit sig_abortLoading();
    ui->pushButton_abortLoading->setEnabled(false);
}

