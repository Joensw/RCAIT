#include "newmodeldialog.h"
#include "ui_newmodeldialog.h"

NewModelDialog::NewModelDialog(QWidget *parent, QStringList classificationPlugins) :
    QDialog(parent),
    ui(new Ui::NewModelDialog)
{
    ui->setupUi(this);

    ui->classificationPluginComboBox->addItems(classificationPlugins);
    connect(ui->classificationPluginComboBox, &QComboBox::currentTextChanged, this, &NewModelDialog::slot_classifactionPlugin_currentTextChanged);
}

NewModelDialog::~NewModelDialog()
{
    delete ui;
}

void NewModelDialog::setAvailableBases(QStringList bases)
{
    ui->pluginProfileComboBox->clear();
    ui->pluginProfileComboBox->addItems(bases);
}

QString NewModelDialog::getCurrentSelectedPlugin()
{
    return ui->classificationPluginComboBox->currentText();
}

void NewModelDialog::on_buttonBox_rejected(){
    this->reject();
}

void NewModelDialog::slot_classifactionPlugin_currentTextChanged(const QString &text)
{
    emit sig_pluginSelected(text);
}

void NewModelDialog::on_buttonBox_accepted(){
    emit sig_newModelConfirm(ui->lineEdit_nameEntry->text(), ui->classificationPluginComboBox->currentText(), ui->pluginProfileComboBox->currentText());
}
