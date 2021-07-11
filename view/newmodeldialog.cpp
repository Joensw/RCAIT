#include "newmodeldialog.h"
#include "ui_newmodeldialog.h"

NewModelDialog::NewModelDialog(QWidget *parent, QStringList classificationPlugins) :
    QDialog(parent),
    ui(new Ui::NewModelDialog)
{
    ui->setupUi(this);

    ui->classificationPluginComboBox->addItems(classificationPlugins);
}

NewModelDialog::~NewModelDialog()
{
    delete ui;
}

void NewModelDialog::on_buttonBox_rejected(){
    this->reject();
}

void NewModelDialog::on_buttonBox_accepted(){
    emit sig_newModelConfirm(ui->lineEdit_nameEntry->text(), ui->classificationPluginComboBox->currentText(), ui->pluginProfileComboBox->currentText());
}
